#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER ekf2

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "../src/modules/ekf2/tp.h"

#if !defined(_TP_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _TP_H

#include <lttng/tracepoint.h>

TRACEPOINT_EVENT(
    ekf2,
    attitude,
    TP_ARGS(float, roll, float, pitch),
    TP_FIELDS(
        ctf_float(float, roll, roll)
        ctf_float(float, pitch, pitch)
    )
)

#endif /* _TP_H */

#include <lttng/tracepoint-event.h>
