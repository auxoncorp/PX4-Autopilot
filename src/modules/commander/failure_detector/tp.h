#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER failure_detector

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "../src/modules/commander/failure_detector/tp.h"

#if !defined(_TP_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _TP_H

#include <lttng/tracepoint.h>

TRACEPOINT_EVENT(
    failure_detector,
    reset_attitude_status,
    TP_ARGS(int, status_changed),
    TP_FIELDS(ctf_integer(int, status_changed, status_changed))
)

TRACEPOINT_EVENT(
    failure_detector,
    updated,
    TP_ARGS(int, updated),
    TP_FIELDS(ctf_integer(int, updated, updated))
)

TRACEPOINT_EVENT(
    failure_detector,
    attitude_stable,
    TP_ARGS(int, attitude_is_stabilized),
    TP_FIELDS(ctf_integer(int, attitude_is_stabilized, attitude_is_stabilized))
)

TRACEPOINT_EVENT(
    failure_detector,
    status_roll_asserted,
    TP_ARGS(int, failure_asserted),
    TP_FIELDS(ctf_integer(int, failure_asserted, failure_asserted))
)

TRACEPOINT_EVENT(
    failure_detector,
    status_pitch_asserted,
    TP_ARGS(int, failure_asserted),
    TP_FIELDS(ctf_integer(int, failure_asserted, failure_asserted))
)

#endif /* _TP_H */

#include <lttng/tracepoint-event.h>
