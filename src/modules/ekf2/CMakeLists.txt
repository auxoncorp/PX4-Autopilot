############################################################################
#
#   Copyright (c) 2015 PX4 Development Team. All rights reserved.
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
#############################################################################

# Keep asserts
add_definitions(-UNDEBUG)

add_subdirectory(Utility)

px4_add_module(
	MODULE modules__ekf2
	MAIN ekf2
	COMPILE_FLAGS
	STACK_MAX 2400
	SRCS
		ekf2_main.cpp
	DEPENDS
		git_ecl
		ecl_EKF
		ecl_geo
		perf
		Ekf2Utility
        modality_helpers
	)

modality_probe_generate_manifest(
    TARGET modules__ekf2
    DEPENDS ekf2_main.cpp
    COMPONENT_NAME "ekf2"
    OUTPUT_PATH "ekf2-component"
    FILE_EXTENSIONS "cpp"
    SOURCE_PATH "."
    )

modality_probe_generate_header(
    TARGET modules__ekf2
    OUTPUT_FILE "ekf2_component_definitions.h"
    COMPONENT_PATH "ekf2-component"
    )
