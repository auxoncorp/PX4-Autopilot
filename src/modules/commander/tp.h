#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER commander

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "../src/modules/commander/tp.h"

#if !defined(_TP_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _TP_H

#include <lttng/tracepoint.h>
#include <stdbool.h>

TRACEPOINT_EVENT(
    commander,
    land_detected,
    TP_ARGS(),
    TP_FIELDS()
)

TRACEPOINT_EVENT(
    commander,
    takeoff_detected,
    TP_ARGS(),
    TP_FIELDS()
)

TRACEPOINT_EVENT(
    commander,
    lockdown_triggered,
    TP_ARGS(),
    TP_FIELDS()
)

TRACEPOINT_EVENT(
    commander,
    flight_terminated,
    TP_ARGS(),
    TP_FIELDS()
)

#endif /* _TP_H */

#include <lttng/tracepoint-event.h>
