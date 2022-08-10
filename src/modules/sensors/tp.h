#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER sensors

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "../src/modules/sensors/tp.h"

#if !defined(_TP_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _TP_H

#include <lttng/tracepoint.h>

TRACEPOINT_EVENT(
    sensors,
    sensors_polled,
    TP_ARGS(),
    TP_FIELDS()
)

#endif /* _TP_H */

#include <lttng/tracepoint-event.h>
