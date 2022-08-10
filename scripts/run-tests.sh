#!/usr/bin/env bash

export PX4_HOME_LAT=45.452075
export PX4_HOME_LON=-122.672064
export PX4_HOME_ALT=0

# If running the GUI, may need these
# See https://github.com/osrf/gazebo/issues/2688
export QT_AUTO_SCREEN_SCALE_FACTOR=0
export QT_SCREEN_SCALE_FACTORS=[1.0,1.0]

TEST_CASE="Takeoff and Land"

./scripts/start-tracing-session.sh

# To run with the GUI, add --gui to the argument list
./test/mavsdk_tests/mavsdk_test_runner.py \
    test/mavsdk_tests/configs/sitl.json \
    --speed-factor 1 \
    --model iris \
    --verbose \
    --case "$TEST_CASE" "$@"
EXIT_CODE=$?

# We expect the tests to fail occasionally
if (( $EXIT_CODE != 0 )); then
    echo "MAVSDK test runner returned a failure"
fi

./scripts/stop-tracing-session.sh

exit 0
