/****************************************************************************
 *
 *   Copyright (c) 2013-2016 PX4 Development Team. All rights reserved.
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

/*
 * @file LandDetector.cpp
 *
 * @author Johan Jansen <jnsn.johan@gmail.com>
 * @author Julian Oes <julian@oes.ch>
 */

#include "LandDetector.h"

#include "land_detector_component_definitions.h"

using namespace time_literals;

namespace land_detector
{

LandDetector::LandDetector() :
	ModuleParams(nullptr),
	ScheduledWorkItem(MODULE_NAME, px4::wq_configurations::nav_and_controllers)
{
    probe_report_socket_init(&_report_socket);

    const size_t err = MODALITY_PROBE_INIT(
            &_probe_storage[0],
            sizeof(_probe_storage),
            PX4_LAND_DETECTOR,
            PX4_WALL_CLOCK_RESOLUTION_NS,
            PX4_WALL_CLOCK_ID,
            &next_persistent_sequence_id,
            NULL, /* No user data needed for our next_persistent_sequence_id implementation */
            &_probe,
            MODALITY_TAGS("px4", "module", "land-detector"),
            "Land detector probe");
    assert(err == MODALITY_PROBE_ERROR_OK);
    LOG_PROBE_INIT(PX4_LAND_DETECTOR);

    hrt_call_init(&_report_call);
    hrt_call_every(
            &_report_call,
            0,
            REPORT_INTERVAL_US,
            (hrt_callout) &set_atomic_bool,
            &_send_report);
}

LandDetector::~LandDetector()
{
	perf_free(_cycle_perf);
}

void LandDetector::start()
{
	ScheduleDelayed(50_ms);
	_vehicle_local_position_sub.registerCallback();
}

void LandDetector::Run()
{
	// push backup schedule
	ScheduleDelayed(50_ms);

	perf_begin(_cycle_perf);

	if (_parameter_update_sub.updated() || (_land_detected.timestamp == 0)) {
		parameter_update_s param_update;
		_parameter_update_sub.copy(&param_update);

		updateParams();
		_update_params();

		_total_flight_time = static_cast<uint64_t>(_param_total_flight_time_high.get()) << 32;
		_total_flight_time |= static_cast<uint32_t>(_param_total_flight_time_low.get());
	}

	actuator_armed_s actuator_armed;

	if (_actuator_armed_sub.update(&actuator_armed)) {
		_armed = actuator_armed.armed;
	}

	vehicle_acceleration_s vehicle_acceleration;

	if (_vehicle_acceleration_sub.update(&vehicle_acceleration)) {
		_acceleration = matrix::Vector3f{vehicle_acceleration.xyz};
	}

	_vehicle_local_position_sub.update(&_vehicle_local_position);
	_vehicle_status_sub.update(&_vehicle_status);

	_update_topics();

	const hrt_abstime now_us = hrt_absolute_time();

	_freefall_hysteresis.set_state_and_update(_get_freefall_state(), now_us);
	_ground_contact_hysteresis.set_state_and_update(_get_ground_contact_state(), now_us);
	_maybe_landed_hysteresis.set_state_and_update(_get_maybe_landed_state(), now_us);
	_landed_hysteresis.set_state_and_update(_get_landed_state(), now_us);
	_ground_effect_hysteresis.set_state_and_update(_get_ground_effect_state(), now_us);

	const bool freefallDetected = _freefall_hysteresis.get_state();
	const bool ground_contactDetected = _ground_contact_hysteresis.get_state();
	const bool maybe_landedDetected = _maybe_landed_hysteresis.get_state();
	const bool landDetected = _landed_hysteresis.get_state();
	const float alt_max = _get_max_altitude() > 0.0f ? _get_max_altitude() : INFINITY;
	const bool in_ground_effect = _ground_effect_hysteresis.get_state();

	// publish at 1 Hz, very first time, or when the result has changed
	if ((hrt_elapsed_time(&_land_detected.timestamp) >= 1_s) ||
	    (_land_detected.landed != landDetected) ||
	    (_land_detected.freefall != freefallDetected) ||
	    (_land_detected.maybe_landed != maybe_landedDetected) ||
	    (_land_detected.ground_contact != ground_contactDetected) ||
	    (_land_detected.in_ground_effect != in_ground_effect) ||
	    (fabsf(_land_detected.alt_max - alt_max) > FLT_EPSILON)) {

        size_t err = MODALITY_PROBE_RECORD_W_BOOL(
                _probe,
                FREEFALL,
                freefallDetected,
                MODALITY_TAGS("px4", "land-detector", "freefall"),
                "Land detector freefall");
        assert(err == MODALITY_PROBE_ERROR_OK);
        err = MODALITY_PROBE_RECORD_W_BOOL(
                _probe,
                GROUND_CONTACT,
                ground_contactDetected,
                MODALITY_TAGS("px4", "land-detector"),
                "Land detector ground contact");
        assert(err == MODALITY_PROBE_ERROR_OK);
        err = MODALITY_PROBE_RECORD_W_BOOL(
                _probe,
                MAYBE_LANDED,
                maybe_landedDetected,
                MODALITY_TAGS("px4", "land-detector"),
                "Land detector might have landed");
        assert(err == MODALITY_PROBE_ERROR_OK);
        err = MODALITY_PROBE_RECORD_W_BOOL(
                _probe,
                LANDED,
                landDetected,
                MODALITY_TAGS("px4", "land-detector"),
                "Land detector currently landed (stage 3)");
        assert(err == MODALITY_PROBE_ERROR_OK);

		if (!landDetected && _land_detected.landed && _takeoff_time == 0) { /* only set take off time once, until disarming */
			// We did take off
			_takeoff_time = now_us;

            err = MODALITY_PROBE_RECORD(
                    _probe,
                    TAKE_OFF_DETECTED,
                    MODALITY_TAGS("px4", "land-detector", "takeoff"),
                    "Take off detected");
            assert(err == MODALITY_PROBE_ERROR_OK);
		}

		_land_detected.landed = landDetected;
		_land_detected.freefall = freefallDetected;
		_land_detected.maybe_landed = maybe_landedDetected;
		_land_detected.ground_contact = ground_contactDetected;
		_land_detected.alt_max = alt_max;
		_land_detected.in_ground_effect = in_ground_effect;
		_land_detected.timestamp = hrt_absolute_time();

        size_t snapshot_size = 0;
        err = modality_probe_produce_snapshot_bytes(
                _probe,
                &_land_detected.snapshot[0],
                sizeof(_land_detected.snapshot),
                &snapshot_size);
        assert(err == MODALITY_PROBE_ERROR_OK);

		_vehicle_land_detected_pub.publish(_land_detected);
	}

	// set the flight time when disarming (not necessarily when landed, because all param changes should
	// happen on the same event and it's better to set/save params while not in armed state)
	if (_takeoff_time != 0 && !_armed && _previous_armed_state) {
		_total_flight_time += now_us - _takeoff_time;
		_takeoff_time = 0;

		uint32_t flight_time = (_total_flight_time >> 32) & 0xffffffff;

		_param_total_flight_time_high.set(flight_time);
		_param_total_flight_time_high.commit_no_notification();

		flight_time = _total_flight_time & 0xffffffff;

		_param_total_flight_time_low.set(flight_time);
		_param_total_flight_time_low.commit_no_notification();
	}

	_previous_armed_state = _armed;

	perf_end(_cycle_perf);

    if(_send_report.load() == true)
    {
        _send_report.store(false);
        send_probe_report(
                _probe,
                _report_socket,
                COLLECTOR_PORT_E,
                _report_buffer,
                sizeof(_report_buffer));
    }

	if (should_exit()) {
		ScheduleClear();
		exit_and_cleanup();
	}
}

} // namespace land_detector
