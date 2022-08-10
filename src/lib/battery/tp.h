#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER battery

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "../src/lib/battery/tp.h"

#if !defined(_TP_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _TP_H

#include <lttng/tracepoint.h>
#include <uORB/topics/battery_status.h>

TRACEPOINT_EVENT(
    battery,
    filtered_voltage,
    TP_ARGS(float, voltage),
    TP_FIELDS(ctf_float(float, voltage, voltage))
)

TRACEPOINT_EVENT(
    battery,
    state_reset,
    TP_ARGS(),
    TP_FIELDS()
)

TRACEPOINT_ENUM(
    battery,
    battery_status,
    TP_ENUM_VALUES(
        ctf_enum_value("NONE", 0)
        ctf_enum_value("LOW", 1)
        ctf_enum_value("CRITICAL", 2)
        ctf_enum_value("EMERGENCY", 3)
        ctf_enum_value("FAILED", 4)
    )
)

TRACEPOINT_EVENT(
    battery,
    warning_level,
    TP_ARGS(uint8_t, level),
    TP_FIELDS(ctf_enum(battery, battery_status, uint8_t, level, level))
)

#endif /* _TP_H */

#include <lttng/tracepoint-event.h>
