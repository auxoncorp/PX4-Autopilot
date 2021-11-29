############################################################################
#
#   Copyright (c) 2015-2019 PX4 Development Team. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name PX4 nor the names of its contributors may be
#    used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
############################################################################

# Keep asserts
add_definitions(-UNDEBUG)

add_subdirectory(data_validator)

add_subdirectory(sensor_calibration) # used by vehicle_{acceleration, angular_velocity, imu}
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(vehicle_acceleration)
add_subdirectory(vehicle_angular_velocity)
add_subdirectory(vehicle_air_data)
add_subdirectory(vehicle_imu)

px4_add_module(
	MODULE modules__sensors
	MAIN sensors
	SRCS
		voted_sensors_update.cpp
		sensors.cpp
		parameters.cpp
	DEPENDS
		airspeed
		conversion
		data_validator
		drivers__device
		git_ecl
		mathlib
		vehicle_acceleration
		vehicle_angular_velocity
		vehicle_air_data
		vehicle_imu
		mag_compensation
        modality_helpers
	)

modality_probe_generate_manifest(
    TARGET modules__sensors
    DEPENDS
        sensors.cpp
        voted_sensors_update.cpp
        vehicle_imu/VehicleIMU.cpp
    COMPONENT_NAME "data-acquisition"
    OUTPUT_PATH "data-acquisition-component"
    FILE_EXTENSIONS "cpp"
    SOURCE_PATH "."
    )

modality_probe_generate_header(
    TARGET modules__sensors
    OUTPUT_FILE "data_acquisition_component_definitions.h"
    COMPONENT_PATH "data-acquisition-component"
    )
