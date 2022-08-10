#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER vehicle_imu

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "../src/modules/sensors/vehicle_imu/tp.h"

#if !defined(_TP_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _TP_H

#include <lttng/tracepoint.h>

TRACEPOINT_EVENT(
    vehicle_imu,
    gyro_integrator_ready,
    TP_ARGS(int, gyro_integrator_ready),
    TP_FIELDS(ctf_integer(int, gyro_integrator_ready, gyro_integrator_ready))
)

#endif /* _TP_H */

#include <lttng/tracepoint-event.h>
