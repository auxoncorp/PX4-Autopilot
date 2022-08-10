#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER gyroscope

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "../src/lib/drivers/gyroscope/tp.h"

#if !defined(_TP_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _TP_H

#include <lttng/tracepoint.h>
#include <uORB/topics/sensor_gyro.h>

TRACEPOINT_EVENT(
    gyroscope,
    sensor_gyro,
    TP_ARGS(const struct sensor_gyro_s*, sensor_gyro),
    TP_FIELDS(
        ctf_float(float, x, sensor_gyro->x)
        ctf_float(float, y, sensor_gyro->y)
        ctf_float(float, z, sensor_gyro->z)
    )
)

#endif /* _TP_H */

#include <lttng/tracepoint-event.h>
