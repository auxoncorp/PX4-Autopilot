/****************************************************************************
 *
 *   Copyright (c) 2016 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file voted_sensors_update.cpp
 *
 * @author Beat Kueng <beat-kueng@gmx.net>
 */

#include "voted_sensors_update.h"

#include <lib/conversion/rotation.h>
#include <lib/ecl/geo/geo.h>
#include <lib/systemlib/mavlink_log.h>
#include <uORB/Subscription.hpp>
#include <uORB/topics/sensor_accel.h>
#include <uORB/topics/sensor_gyro.h>

#include "sensors_probe.h"

#define MAG_ROT_VAL_INTERNAL		-1
#define CAL_ERROR_APPLY_CAL_MSG "FAILED APPLYING %s CAL #%u"

using namespace sensors;
using namespace matrix;
using namespace time_literals;
using math::radians;

VotedSensorsUpdate::VotedSensorsUpdate(const Parameters &parameters, bool hil_enabled,
				       uORB::SubscriptionCallbackWorkItem(&vehicle_imu_sub)[3]) :
	ModuleParams(nullptr),
	_vehicle_imu_sub(vehicle_imu_sub),
	_parameters(parameters),
	_hil_enabled(hil_enabled),
	_mag_compensator(this)
{
	_mag.voter.set_timeout(300000);
	_mag.voter.set_equal_value_threshold(1000);

	if (_hil_enabled) { // HIL has less accurate timing so increase the timeouts a bit
		_gyro.voter.set_timeout(500000);
		_accel.voter.set_timeout(500000);
	}
}

int VotedSensorsUpdate::init(sensor_combined_s &raw)
{
	raw.accelerometer_timestamp_relative = sensor_combined_s::RELATIVE_TIMESTAMP_INVALID;
	raw.timestamp = 0;

	initializeSensors();

	_selection_changed = true;

	return 0;
}

void VotedSensorsUpdate::initializeSensors()
{
	initSensorClass(_gyro, GYRO_COUNT_MAX);
	initSensorClass(_accel, ACCEL_COUNT_MAX);
	initSensorClass(_mag, MAG_COUNT_MAX);
}

void VotedSensorsUpdate::parametersUpdate()
{
	updateParams();

	/* fine tune board offset */
	const Dcmf board_rotation_offset{Eulerf{radians(_parameters.board_offset[0]), radians(_parameters.board_offset[1]), radians(_parameters.board_offset[2])}};

	_board_rotation = board_rotation_offset * get_rot_matrix((enum Rotation)_parameters.board_rotation);

	// initialze all mag rotations with the board rotation in case there is no calibration data available
	for (int topic_instance = 0; topic_instance < MAG_COUNT_MAX; ++topic_instance) {
		_mag_rotation[topic_instance] = _board_rotation;
	}

	/* set offset parameters to new values */
	bool failed = false;

	// run through all IMUs
	for (uint8_t uorb_index = 0; uorb_index < math::max(ACCEL_COUNT_MAX, GYRO_COUNT_MAX); uorb_index++) {
		uORB::SubscriptionData<vehicle_imu_s> imu{ORB_ID(vehicle_imu), uorb_index};
		imu.update();

		if (imu.get().timestamp > 0 && imu.get().accel_device_id > 0 && imu.get().gyro_device_id > 0) {

			if (_accel.priority[uorb_index] == ORB_PRIO_UNINITIALIZED) {
				// find corresponding sensor_accel publication
				for (uint8_t i = 0; i < ACCEL_COUNT_MAX; i++) {
					uORB::SubscriptionData<sensor_accel_s> sensor_accel{ORB_ID(sensor_accel), i};
					sensor_accel.update();

					if (imu.get().accel_device_id == sensor_accel.get().device_id) {
						_accel.priority[uorb_index] = sensor_accel.get_priority();
						break;
					}
				}
			}

			if (_gyro.priority[uorb_index] == ORB_PRIO_UNINITIALIZED) {
				// find corresponding sensor_gyro publication
				for (uint8_t i = 0; i < GYRO_COUNT_MAX; i++) {
                    /* Fixed in 27f23ac290e3fbfc3d28c08bfd535c12eb42eebf */
					/* uORB::SubscriptionData<sensor_accel_s> sensor_gyro{ORB_ID(sensor_gyro), i}; */
					uORB::SubscriptionData<sensor_gyro_s> sensor_gyro{ORB_ID(sensor_gyro), i};
					sensor_gyro.update();

					if (imu.get().gyro_device_id == sensor_gyro.get().device_id) {
						_gyro.priority[uorb_index] = sensor_gyro.get_priority();
						break;
					}
				}
			}
		}
	}


	/* run through all mag sensors
	 * Because we store the device id in _mag_device_id, we need to get the id via uorb topic since
	 * the DevHandle method does not work on POSIX.
	 */

	/* first we have to reset all possible mags, since we are looping through the uORB instances instead of the drivers,
	 * and not all uORB instances have to be published yet at the initial call of parametersUpdate()
	 */
	for (int i = 0; i < MAG_COUNT_MAX; i++) {
		_mag.enabled[i] = true;
	}

	for (int topic_instance = 0; topic_instance < MAG_COUNT_MAX
	     && topic_instance < _mag.subscription_count; ++topic_instance) {

		sensor_mag_s report{};

		if (!_mag.subscription[topic_instance].copy(&report)) {
			continue;
		}

		uint32_t topic_device_id = report.device_id;
		bool is_external = report.is_external;
		_mag_device_id[topic_instance] = topic_device_id;

		// find the driver handle that matches the topic_device_id
		int fd = -1;
		char str[30] {};

		for (unsigned driver_index = 0; driver_index < MAG_COUNT_MAX; ++driver_index) {

			(void)sprintf(str, "%s%u", MAG_BASE_DEVICE_PATH, driver_index);

			fd = px4_open(str, O_RDWR);

			if (fd < 0) {
				/* the driver is not running, continue with the next */
				continue;
			}

			uint32_t driver_device_id = (uint32_t)px4_ioctl(fd, DEVIOCGDEVICEID, 0);

			if (driver_device_id == topic_device_id) {
				break; // we found the matching driver

			} else {
				px4_close(fd);
			}
		}

		bool config_ok = false;

		/* run through all stored calibrations */
		for (unsigned i = 0; i < MAG_COUNT_MAX; i++) {
			/* initially status is ok per config */
			failed = false;

			(void)sprintf(str, "CAL_MAG%u_ID", i);
			int32_t device_id = 0;
			failed = failed || (PX4_OK != param_get(param_find(str), &device_id));

			(void)sprintf(str, "CAL_MAG%u_EN", i);
			int32_t device_enabled = 1;
			failed = failed || (PX4_OK != param_get(param_find(str), &device_enabled));

			if (failed) {
				continue;
			}

			/* if the calibration is for this device, apply it */
			if ((uint32_t)device_id == _mag_device_id[topic_instance]) {
				_mag.enabled[topic_instance] = (device_enabled == 1);
				_mag.power_compensation[topic_instance] = {_parameters.mag_comp_paramX[i], _parameters.mag_comp_paramY[i], _parameters.mag_comp_paramZ[i]};

				// the mags that were published after the initial parameterUpdate
				// would be given the priority even if disabled. Reset it to 0 in this case
				if (!_mag.enabled[topic_instance]) {
					_mag.priority[topic_instance] = ORB_PRIO_UNINITIALIZED;
				}

				mag_calibration_s mscale{};

				(void)sprintf(str, "CAL_MAG%u_XOFF", i);
				failed = failed || (PX4_OK != param_get(param_find(str), &mscale.x_offset));

				(void)sprintf(str, "CAL_MAG%u_YOFF", i);
				failed = failed || (PX4_OK != param_get(param_find(str), &mscale.y_offset));

				(void)sprintf(str, "CAL_MAG%u_ZOFF", i);
				failed = failed || (PX4_OK != param_get(param_find(str), &mscale.z_offset));

				(void)sprintf(str, "CAL_MAG%u_XSCALE", i);
				failed = failed || (PX4_OK != param_get(param_find(str), &mscale.x_scale));

				(void)sprintf(str, "CAL_MAG%u_YSCALE", i);
				failed = failed || (PX4_OK != param_get(param_find(str), &mscale.y_scale));

				(void)sprintf(str, "CAL_MAG%u_ZSCALE", i);
				failed = failed || (PX4_OK != param_get(param_find(str), &mscale.z_scale));

				(void)sprintf(str, "CAL_MAG%u_ROT", i);
				int32_t mag_rot = 0;
				param_get(param_find(str), &mag_rot);

				if (is_external) {

					/* check if this mag is still set as internal, otherwise leave untouched */
					if (mag_rot < 0) {
						/* it was marked as internal, change to external with no rotation */
						mag_rot = 0;
						param_set_no_notification(param_find(str), &mag_rot);
					}

				} else {
					/* mag is internal - reset param to -1 to indicate internal mag */
					if (mag_rot != MAG_ROT_VAL_INTERNAL) {
						mag_rot = MAG_ROT_VAL_INTERNAL;
						param_set_no_notification(param_find(str), &mag_rot);
					}
				}

				/* now get the mag rotation */
				if (mag_rot >= 0) {
					// Set external magnetometers to use the parameter value
					_mag_rotation[topic_instance] = get_rot_matrix((enum Rotation)mag_rot);

				} else {
					// Set internal magnetometers to use the board rotation
					_mag_rotation[topic_instance] = _board_rotation;
				}

				if (failed) {
					PX4_ERR(CAL_ERROR_APPLY_CAL_MSG, "mag", i);

				} else {

					/* apply new scaling and offsets */
					config_ok = (px4_ioctl(fd, MAGIOCSSCALE, (long unsigned int)&mscale) == 0);

					if (!config_ok) {
						PX4_ERR(CAL_ERROR_APPLY_CAL_MSG, "mag ", i);
					}
				}

				break;
			}
		}

		px4_close(fd);
	}

}

void VotedSensorsUpdate::imuPoll(struct sensor_combined_s &raw)
{
	for (int uorb_index = 0; uorb_index < 3; uorb_index++) {
		vehicle_imu_s imu_report;

		if (_accel.enabled[uorb_index] && _gyro.enabled[uorb_index] && _vehicle_imu_sub[uorb_index].update(&imu_report)) {
            const size_t err = modality_probe_merge_snapshot_bytes(
                    g_sensors_probe,
                    &imu_report.snapshot[0],
                    sizeof(imu_report.snapshot));
            assert(err == MODALITY_PROBE_ERROR_OK);

			// copy corresponding vehicle_imu_status for accel & gyro error counts
			vehicle_imu_status_s imu_status{};
			_vehicle_imu_status_sub[uorb_index].copy(&imu_status);

			// First publication with data
			if (_accel.priority[uorb_index] == 0) {
				_accel.priority[uorb_index] = _accel.subscription[uorb_index].get_priority();
			}

			if (_gyro.priority[uorb_index] == 0) {
				_gyro.priority[uorb_index] = _gyro.subscription[uorb_index].get_priority();
			}

			_accel_device_id[uorb_index] = imu_report.accel_device_id;
			_gyro_device_id[uorb_index] = imu_report.gyro_device_id;

			// convert the delta velocities to an equivalent acceleration
			const float accel_dt_inv = 1.e6f / (float)imu_report.delta_velocity_dt;
			Vector3f accel_data = Vector3f{imu_report.delta_velocity} * accel_dt_inv;


			// convert the delta angles to an equivalent angular rate
			const float gyro_dt_inv = 1.e6f / (float)imu_report.delta_angle_dt;
			Vector3f gyro_rate = Vector3f{imu_report.delta_angle} * gyro_dt_inv;

			_last_sensor_data[uorb_index].timestamp = imu_report.timestamp_sample;
			_last_sensor_data[uorb_index].accelerometer_m_s2[0] = accel_data(0);
			_last_sensor_data[uorb_index].accelerometer_m_s2[1] = accel_data(1);
			_last_sensor_data[uorb_index].accelerometer_m_s2[2] = accel_data(2);
			_last_sensor_data[uorb_index].accelerometer_integral_dt = imu_report.delta_velocity_dt;
			_last_sensor_data[uorb_index].accelerometer_clipping = imu_report.delta_velocity_clipping;
			_last_sensor_data[uorb_index].gyro_rad[0] = gyro_rate(0);
			_last_sensor_data[uorb_index].gyro_rad[1] = gyro_rate(1);
			_last_sensor_data[uorb_index].gyro_rad[2] = gyro_rate(2);
			_last_sensor_data[uorb_index].gyro_integral_dt = imu_report.delta_angle_dt;


			_last_accel_timestamp[uorb_index] = imu_report.timestamp_sample;

			_accel.voter.put(uorb_index, imu_report.timestamp, _last_sensor_data[uorb_index].accelerometer_m_s2,
					 imu_status.accel_error_count, _accel.priority[uorb_index]);

			_gyro.voter.put(uorb_index, imu_report.timestamp, _last_sensor_data[uorb_index].gyro_rad,
					imu_status.gyro_error_count, _gyro.priority[uorb_index]);
		}
	}

	// find the best sensor
	int accel_best_index;
	int gyro_best_index;
	_accel.voter.get_best(hrt_absolute_time(), &accel_best_index);
	_gyro.voter.get_best(hrt_absolute_time(), &gyro_best_index);

	checkFailover(_accel, "Accel", subsystem_info_s::SUBSYSTEM_TYPE_ACC);
	checkFailover(_gyro, "Gyro", subsystem_info_s::SUBSYSTEM_TYPE_GYRO);

	// write data for the best sensor to output variables
	if ((accel_best_index >= 0) && (gyro_best_index >= 0)) {
		raw.timestamp = _last_sensor_data[gyro_best_index].timestamp;
		memcpy(&raw.accelerometer_m_s2, &_last_sensor_data[accel_best_index].accelerometer_m_s2,
		       sizeof(raw.accelerometer_m_s2));
		memcpy(&raw.gyro_rad, &_last_sensor_data[gyro_best_index].gyro_rad, sizeof(raw.gyro_rad));
		raw.accelerometer_integral_dt = _last_sensor_data[accel_best_index].accelerometer_integral_dt;
		raw.gyro_integral_dt = _last_sensor_data[gyro_best_index].gyro_integral_dt;
		raw.accelerometer_clipping = _last_sensor_data[accel_best_index].accelerometer_clipping;

		if ((accel_best_index != _accel.last_best_vote) || (_selection.accel_device_id != _accel_device_id[accel_best_index])) {
			_accel.last_best_vote = (uint8_t)accel_best_index;
			_selection.accel_device_id = _accel_device_id[accel_best_index];
			_selection_changed = true;
		}

		if ((_gyro.last_best_vote != gyro_best_index) || (_selection.gyro_device_id != _gyro_device_id[gyro_best_index])) {
			_gyro.last_best_vote = (uint8_t)gyro_best_index;
			_selection.gyro_device_id = _gyro_device_id[gyro_best_index];
			_selection_changed = true;

			// clear all registered callbacks
			for (auto &sub : _vehicle_imu_sub) {
				sub.unregisterCallback();
			}

			for (int i = 0; i < GYRO_COUNT_MAX; i++) {
				vehicle_imu_s report{};

				if (_vehicle_imu_sub[i].copy(&report)) {
					if ((report.gyro_device_id != 0) && (report.gyro_device_id == _gyro_device_id[gyro_best_index])) {
						_vehicle_imu_sub[i].registerCallback();
					}
				}
			}
		}
	}
}

void VotedSensorsUpdate::magPoll(vehicle_magnetometer_s &magnetometer)
{
	for (int uorb_index = 0; uorb_index < _mag.subscription_count; uorb_index++) {
		sensor_mag_s mag_report;

		if (_mag.enabled[uorb_index] && _mag.subscription[uorb_index].update(&mag_report)) {

			// force parameter update (loads calibration) if device id still isn't set
			if (_mag_device_id[uorb_index] == 0) {
				parametersUpdate();
			}

			// First publication with data
			if (_mag.priority[uorb_index] == 0) {
				_mag.priority[uorb_index] = _mag.subscription[uorb_index].get_priority();
			}

			Vector3f vect(mag_report.x, mag_report.y, mag_report.z);

			//throttle-/current-based mag compensation
			_mag_compensator.calculate_mag_corrected(vect, _mag.power_compensation[uorb_index]);

			vect = _mag_rotation[uorb_index] * vect;

			_last_magnetometer[uorb_index].timestamp = mag_report.timestamp;
			_last_magnetometer[uorb_index].magnetometer_ga[0] = vect(0);
			_last_magnetometer[uorb_index].magnetometer_ga[1] = vect(1);
			_last_magnetometer[uorb_index].magnetometer_ga[2] = vect(2);

			_mag.voter.put(uorb_index, mag_report.timestamp, _last_magnetometer[uorb_index].magnetometer_ga, mag_report.error_count,
				       _mag.priority[uorb_index]);
		}
	}

	int best_index;
	_mag.voter.get_best(hrt_absolute_time(), &best_index);

	checkFailover(_mag, "Mag", subsystem_info_s::SUBSYSTEM_TYPE_MAG);

	if (best_index >= 0) {
		magnetometer = _last_magnetometer[best_index];
		_mag.last_best_vote = (uint8_t)best_index;

		if (_selection.mag_device_id != _mag_device_id[best_index]) {
			_selection_changed = true;
			_selection.mag_device_id = _mag_device_id[best_index];
		}
	}
}

bool VotedSensorsUpdate::checkFailover(SensorData &sensor, const char *sensor_name, const uint64_t type)
{
	if (sensor.last_failover_count != sensor.voter.failover_count() && !_hil_enabled) {

		uint32_t flags = sensor.voter.failover_state();
		int failover_index = sensor.voter.failover_index();

		if (flags == DataValidator::ERROR_FLAG_NO_ERROR) {
			if (failover_index != -1) {
				// we switched due to a non-critical reason. No need to panic.
				PX4_INFO("%s sensor switch from #%i", sensor_name, failover_index);
			}

		} else {
			if (failover_index != -1) {

				const hrt_abstime now = hrt_absolute_time();

				if (now - _last_error_message > 3_s) {
					mavlink_log_emergency(&_mavlink_log_pub, "%s #%i fail: %s%s%s%s%s!",
							      sensor_name,
							      failover_index,
							      ((flags & DataValidator::ERROR_FLAG_NO_DATA) ? " OFF" : ""),
							      ((flags & DataValidator::ERROR_FLAG_STALE_DATA) ? " STALE" : ""),
							      ((flags & DataValidator::ERROR_FLAG_TIMEOUT) ? " TIMEOUT" : ""),
							      ((flags & DataValidator::ERROR_FLAG_HIGH_ERRCOUNT) ? " ERR CNT" : ""),
							      ((flags & DataValidator::ERROR_FLAG_HIGH_ERRDENSITY) ? " ERR DNST" : ""));
					_last_error_message = now;
				}

				// reduce priority of failed sensor to the minimum
				sensor.priority[failover_index] = ORB_PRIO_MIN;

				int ctr_valid = 0;

				for (uint8_t i = 0; i < sensor.subscription_count; i++) {
					if (sensor.enabled[i] && (sensor.priority[i] > ORB_PRIO_MIN)) {
						ctr_valid++;
					}
				}

				if (ctr_valid < 2) {
					if (ctr_valid == 0) {
						// Zero valid sensors remain! Set even the primary sensor health to false
						_info.subsystem_type = type;

					} else if (ctr_valid == 1) {
						// One valid sensor remains, set secondary sensor health to false
						if (type == subsystem_info_s::SUBSYSTEM_TYPE_GYRO) { _info.subsystem_type = subsystem_info_s::SUBSYSTEM_TYPE_GYRO2; }

						if (type == subsystem_info_s::SUBSYSTEM_TYPE_ACC) { _info.subsystem_type = subsystem_info_s::SUBSYSTEM_TYPE_ACC2; }

						if (type == subsystem_info_s::SUBSYSTEM_TYPE_MAG) { _info.subsystem_type = subsystem_info_s::SUBSYSTEM_TYPE_MAG2; }
					}

					_info.timestamp = hrt_absolute_time();
					_info.present = true;
					_info.enabled = true;
					_info.ok = false;

					_info_pub.publish(_info);
				}
			}
		}

		sensor.last_failover_count = sensor.voter.failover_count();
		return true;
	}

	return false;
}

void VotedSensorsUpdate::initSensorClass(SensorData &sensor_data, uint8_t sensor_count_max)
{
	bool added = false;
	int max_sensor_index = -1;

	for (unsigned i = 0; i < sensor_count_max; i++) {

		max_sensor_index = i;

		if (!sensor_data.advertised[i] && sensor_data.subscription[i].advertised()) {
			sensor_data.advertised[i] = true;

			if (i > 0) {
				/* the first always exists, but for each further sensor, add a new validator */
				if (sensor_data.voter.add_new_validator()) {
					added = true;

				} else {
					PX4_ERR("failed to add validator for sensor %s %i", sensor_data.subscription[i].get_topic()->o_name, i);
				}
			}
		}
	}

	// never decrease the sensor count, as we could end up with mismatching validators
	if (max_sensor_index + 1 > sensor_data.subscription_count) {
		sensor_data.subscription_count = max_sensor_index + 1;
	}

	if (added) {
		// force parameter refresh if anything was added
		parametersUpdate();
	}
}

void VotedSensorsUpdate::printStatus()
{
	PX4_INFO("selected gyro: %d (%d)", _selection.gyro_device_id, _gyro.last_best_vote);
	_gyro.voter.print();

	PX4_INFO_RAW("\n");
	PX4_INFO("selected accel: %d (%d)", _selection.accel_device_id, _accel.last_best_vote);
	_accel.voter.print();

	PX4_INFO_RAW("\n");
	PX4_INFO("selected mag: %d (%d)", _selection.mag_device_id, _mag.last_best_vote);
	_mag.voter.print();
}

void VotedSensorsUpdate::sensorsPoll(sensor_combined_s &raw, vehicle_magnetometer_s &magnetometer)
{
	imuPoll(raw);
	magPoll(magnetometer);

	// publish sensor selection if changed
	if (_selection_changed) {
		// don't publish until selected IDs are valid
		if (_selection.accel_device_id > 0 && _selection.gyro_device_id > 0) {
			_selection.timestamp = hrt_absolute_time();
			_sensor_selection_pub.publish(_selection);
			_selection_changed = false;
		}
	}
}

void VotedSensorsUpdate::setRelativeTimestamps(sensor_combined_s &raw)
{
	if (_last_accel_timestamp[_accel.last_best_vote]) {
		raw.accelerometer_timestamp_relative = (int32_t)((int64_t)_last_accel_timestamp[_accel.last_best_vote] -
						       (int64_t)raw.timestamp);
	}
}

void
VotedSensorsUpdate::calcAccelInconsistency(sensor_preflight_s &preflt)
{
	float accel_diff_sum_max_sq = 0.0f; // the maximum sum of axis differences squared
	unsigned check_index = 0; // the number of sensors the primary has been checked against

	// Check each sensor against the primary
	for (int sensor_index = 0; sensor_index < _accel.subscription_count; sensor_index++) {

		// check that the sensor we are checking against is not the same as the primary
		if (_accel.enabled[sensor_index] && (_accel.priority[sensor_index] > 0) && (sensor_index != _accel.last_best_vote)) {

			float accel_diff_sum_sq = 0.0f; // sum of differences squared for a single sensor comparison agains the primary

			// calculate accel_diff_sum_sq for the specified sensor against the primary
			for (unsigned axis_index = 0; axis_index < 3; axis_index++) {
				_accel_diff[axis_index][check_index] = 0.95f * _accel_diff[axis_index][check_index] + 0.05f *
								       (_last_sensor_data[_accel.last_best_vote].accelerometer_m_s2[axis_index] -
									_last_sensor_data[sensor_index].accelerometer_m_s2[axis_index]);
				accel_diff_sum_sq += _accel_diff[axis_index][check_index] * _accel_diff[axis_index][check_index];

			}

			// capture the largest sum value
			if (accel_diff_sum_sq > accel_diff_sum_max_sq) {
				accel_diff_sum_max_sq = accel_diff_sum_sq;

			}

			// increment the check index
			check_index++;
		}

		// check to see if the maximum number of checks has been reached and break
		if (check_index >= 2) {
			break;

		}
	}

	// skip check if less than 2 sensors
	if (check_index < 1) {
		preflt.accel_inconsistency_m_s_s = 0.0f;

	} else {
		// get the vector length of the largest difference and write to the combined sensor struct
		preflt.accel_inconsistency_m_s_s = sqrtf(accel_diff_sum_max_sq);
	}
}

void VotedSensorsUpdate::calcGyroInconsistency(sensor_preflight_s &preflt)
{
	float gyro_diff_sum_max_sq = 0.0f; // the maximum sum of axis differences squared
	unsigned check_index = 0; // the number of sensors the primary has been checked against

	// Check each sensor against the primary
	for (int sensor_index = 0; sensor_index < _gyro.subscription_count; sensor_index++) {

		// check that the sensor we are checking against is not the same as the primary
		if (_gyro.enabled[sensor_index] && (_gyro.priority[sensor_index] > 0) && (sensor_index != _gyro.last_best_vote)) {

			float gyro_diff_sum_sq = 0.0f; // sum of differences squared for a single sensor comparison against the primary

			// calculate gyro_diff_sum_sq for the specified sensor against the primary
			for (unsigned axis_index = 0; axis_index < 3; axis_index++) {
				_gyro_diff[axis_index][check_index] = 0.95f * _gyro_diff[axis_index][check_index] + 0.05f *
								      (_last_sensor_data[_gyro.last_best_vote].gyro_rad[axis_index] -
								       _last_sensor_data[sensor_index].gyro_rad[axis_index]);
				gyro_diff_sum_sq += _gyro_diff[axis_index][check_index] * _gyro_diff[axis_index][check_index];

			}

			// capture the largest sum value
			if (gyro_diff_sum_sq > gyro_diff_sum_max_sq) {
				gyro_diff_sum_max_sq = gyro_diff_sum_sq;

			}

			// increment the check index
			check_index++;
		}

		// check to see if the maximum number of checks has been reached and break
		if (check_index >= 2) {
			break;

		}
	}

	// skip check if less than 2 sensors
	if (check_index < 1) {
		preflt.gyro_inconsistency_rad_s = 0.0f;

	} else {
		// get the vector length of the largest difference and write to the combined sensor struct
		preflt.gyro_inconsistency_rad_s = sqrtf(gyro_diff_sum_max_sq);
	}
}

void VotedSensorsUpdate::calcMagInconsistency(sensor_preflight_s &preflt)
{
	Vector3f primary_mag(_last_magnetometer[_mag.last_best_vote].magnetometer_ga); // primary mag field vector
	float mag_angle_diff_max = 0.0f; // the maximum angle difference
	unsigned check_index = 0; // the number of sensors the primary has been checked against

	// Check each sensor against the primary
	for (int i = 0; i < _mag.subscription_count; i++) {
		// check that the sensor we are checking against is not the same as the primary
		if (_mag.enabled[i] && (_mag.priority[i] > 0) && (i != _mag.last_best_vote)) {
			// calculate angle to 3D magnetic field vector of the primary sensor
			Vector3f current_mag(_last_magnetometer[i].magnetometer_ga);
			float angle_error = AxisAnglef(Quatf(current_mag, primary_mag)).angle();

			// complementary filter to not fail/pass on single outliers
			_mag_angle_diff[check_index] *= 0.95f;
			_mag_angle_diff[check_index] += 0.05f * angle_error;

			mag_angle_diff_max = math::max(mag_angle_diff_max, _mag_angle_diff[check_index]);

			// increment the check index
			check_index++;
		}

		// check to see if the maximum number of checks has been reached and break
		if (check_index >= 2) {
			break;
		}
	}

	// get the vector length of the largest difference and write to the combined sensor struct
	// will be zero if there is only one magnetometer and hence nothing to compare
	preflt.mag_inconsistency_angle = mag_angle_diff_max;
}

void VotedSensorsUpdate::update_mag_comp_armed(bool armed)
{
	_mag_compensator.update_armed_flag(armed);
}

void VotedSensorsUpdate::update_mag_comp_power(float power)
{
	_mag_compensator.update_power(power);
}
