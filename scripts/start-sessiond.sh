#!/usr/bin/env bash

source scripts/lttng-env.sh

lttng-sessiond --no-kernel

exit 0
