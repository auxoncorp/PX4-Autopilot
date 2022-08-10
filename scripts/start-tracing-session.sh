#!/usr/bin/env bash

source scripts/lttng-env.sh

lttng create px4

lttng enable-event --userspace battery:'*'
lttng enable-event --userspace land_detector:'*'
lttng enable-event --userspace gyroscope:'*'
lttng enable-event --userspace sensors:'*'
lttng enable-event --userspace vehicle_imu:'*'
lttng enable-event --userspace ekf2:'*'
lttng enable-event --userspace commander:'*'
lttng enable-event --userspace failure_detector:'*'

lttng start px4

exit 0
