#!/usr/bin/env bash

source scripts/lttng-env.sh

lttng stop px4
lttng destroy px4

exit 0
