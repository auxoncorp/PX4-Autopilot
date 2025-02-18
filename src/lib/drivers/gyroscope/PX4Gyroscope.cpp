/****************************************************************************
 *
 *   Copyright (c) 2018-2020 PX4 Development Team. All rights reserved.
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


#include "PX4Gyroscope.hpp"

#include <lib/drivers/device/Device.hpp>

#include "gyroscope_component_definitions.h"
#include "generated_mutators/gyroscope_mutator.h"

using namespace time_literals;
using matrix::Vector3f;

static constexpr int32_t sum(const int16_t samples[16], uint8_t len)
{
	int32_t sum = 0;

	for (int n = 0; n < len; n++) {
		sum += samples[n];
	}

	return sum;
}

PX4Gyroscope::PX4Gyroscope(uint32_t device_id, ORB_PRIO priority, enum Rotation rotation) :
	ModuleParams(nullptr),
	_sensor_pub{ORB_ID(sensor_gyro), priority},
	_sensor_fifo_pub{ORB_ID(sensor_gyro_fifo), priority},
	_device_id{device_id},
	_rotation{rotation}
{
	// advertise immediately to keep instance numbering in sync
	_sensor_pub.advertise();

	updateParams();

    probe_report_socket_init(&_report_socket);
    _ctrl_msg_recvr = udp_control_message_receiver_new();
    assert(_ctrl_msg_recvr != NULL);
    size_t err = udp_control_message_receiver_run(UDP_CONTROL_RECVR_GYROSCOPE, _ctrl_msg_recvr);
    assert(err == 0);

    err = MODALITY_PROBE_INIT(
            &_probe_storage[0],
            sizeof(_probe_storage),
            GYROSCOPE,
            PX4_WALL_CLOCK_RESOLUTION_NS,
            PX4_WALL_CLOCK_ID,
            &next_persistent_sequence_id,
            NULL, /* No user data needed for our next_persistent_sequence_id implementation */
            &_probe,
            MODALITY_TAGS("px4", "library", "gyroscope", "sensor", "control-plane"),
            "Gyroscope probe");
    assert(err == MODALITY_PROBE_ERROR_OK);
    LOG_PROBE_INIT_W_RECVR(GYROSCOPE, UDP_CONTROL_RECVR_GYROSCOPE);

    hrt_call_init(&_report_call);
    hrt_call_every(
            &_report_call,
            0,
            REPORT_INTERVAL_US,
            (hrt_callout) &set_atomic_bool,
            &_send_report);

    hrt_call_init(&_mutator_announcement_call);
    hrt_call_every(
            &_mutator_announcement_call,
            0,
            MUTATOR_ANNOUNCEMENT_INTERVAL_US,
            (hrt_callout) &set_atomic_bool,
            &_send_mutator_announcement);

    hrt_call_init(&_log_data_call);
    hrt_call_every(
            &_log_data_call,
            0,
            SAMPLE_LOG_INTERVAL_US,
            (hrt_callout) &set_atomic_bool,
            &_log_data);
}

PX4Gyroscope::~PX4Gyroscope()
{
	_sensor_pub.unadvertise();
	_sensor_fifo_pub.unadvertise();
}

void PX4Gyroscope::set_device_type(uint8_t devtype)
{
	// current DeviceStructure
	union device::Device::DeviceId device_id;
	device_id.devid = _device_id;

	// update to new device type
	device_id.devid_s.devtype = devtype;

	// copy back
	_device_id = device_id.devid;
}

void PX4Gyroscope::update(const hrt_abstime &timestamp_sample, float x, float y, float z)
{
	// publish
	Publish(timestamp_sample, x, y, z);
}

void PX4Gyroscope::updateFIFO(sensor_gyro_fifo_s &sample)
{
	// publish fifo
	sample.device_id = _device_id;
	sample.scale = _scale;
	sample.rotation = _rotation;

	sample.timestamp = hrt_absolute_time();
	_sensor_fifo_pub.publish(sample);

	{
		// trapezoidal integration (equally spaced, scaled by dt later)
		const uint8_t N = sample.samples;
		const Vector3f integral{
			(0.5f * (_last_sample[0] + sample.x[N - 1]) + sum(sample.x, N - 1)),
			(0.5f * (_last_sample[1] + sample.y[N - 1]) + sum(sample.y, N - 1)),
			(0.5f * (_last_sample[2] + sample.z[N - 1]) + sum(sample.z, N - 1)),
		};

		_last_sample[0] = sample.x[N - 1];
		_last_sample[1] = sample.y[N - 1];
		_last_sample[2] = sample.z[N - 1];

		const float x = integral(0) / (float)N;
		const float y = integral(1) / (float)N;
		const float z = integral(2) / (float)N;

		// publish
		Publish(sample.timestamp_sample, x, y, z);
	}
}

void PX4Gyroscope::merge_snapshot(const uint8_t * const snapshot, const size_t snapshot_size)
{
    assert(_probe != NULL);
    assert(snapshot != NULL);
    const size_t err = modality_probe_merge_snapshot_bytes(
            _probe,
            snapshot,
            snapshot_size);
    assert(err == 0);
}

void PX4Gyroscope::Publish(const hrt_abstime &timestamp_sample, float x, float y, float z)
{
    size_t err;

	// Apply rotation (before scaling)
	rotate_3f(_rotation, x, y, z);

	sensor_gyro_s report;

	report.timestamp_sample = timestamp_sample;
	report.device_id = _device_id;
	report.temperature = _temperature;
	report.error_count = _error_count;
	report.x = x * _scale;
	report.y = y * _scale;
	report.z = z * _scale;
	report.timestamp = hrt_absolute_time();

    /* Generate a mutator that exposes the 'report.z' data as a parameter (units in radians/second) */
    MODALITY_MUTATOR(
            _probe,
            GYROSCOPE_MUTATOR,
            z_axis,
            MODALITY_PARAM_DEF(
                F32,
                0.0f,
                NOMINAL(-34.90659f, 34.90659f), /* 2000 deg/s == 34.90659 rad/s */
                SAFETY(-34.90659f, 34.90659f),
                HARD(-34.90659f, 34.90659f)),
            &report.z,
            sizeof(report.z),
            MODALITY_TAGS("px4", "gyroscope"));

    if(_log_data.load() == true)
    {
        _log_data.store(false);
        err = MODALITY_PROBE_RECORD_W_F32_W_TIME(
                _probe,
                ROLL_ANGULAR_RATE,
                report.x,
                US_TO_NS(report.timestamp),
                MODALITY_TAGS("px4", "gyroscope", "sensor", "time"),
                "Gyroscope x axis roll angular rate [radians/second]");
        assert(err == 0);
        err = MODALITY_PROBE_RECORD_W_F32_W_TIME(
                _probe,
                PITCH_ANGULAR_RATE,
                report.y,
                US_TO_NS(report.timestamp),
                MODALITY_TAGS("px4", "gyroscope", "sensor", "time"),
                "Gyroscope y axis pitch angular rate [radians/second]");
        assert(err == 0);
        err = MODALITY_PROBE_RECORD_W_F32_W_TIME(
                _probe,
                YAW_ANGULAR_RATE,
                report.z,
                US_TO_NS(report.timestamp),
                MODALITY_TAGS("px4", "gyroscope", "sensor", "time"),
                "Gyroscope z axis yaw angular rate [radians/second]");
        assert(err == 0);
    }

    size_t snapshot_size = 0;
    err = modality_probe_produce_snapshot_bytes(
            _probe,
            &report.snapshot[0],
            sizeof(report.snapshot),
            &snapshot_size);
    assert(err == MODALITY_PROBE_ERROR_OK);

	_sensor_pub.publish(report);

    if(_send_report.load() == true)
    {
        _send_report.store(false);
        send_probe_report(
                _probe,
                _report_socket,
                COLLECTOR_PORT_D,
                _report_buffer,
                sizeof(_report_buffer));
    }

    if(_send_mutator_announcement.load() == true)
    {
        _send_mutator_announcement.store(false);
        send_mutator_announcement(
                _probe,
                _report_socket,
                COLLECTOR_PORT_A,
                _report_buffer,
                sizeof(_report_buffer));
    }
}
