#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER land_detector

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "../src/modules/land_detector/tp.h"

#if !defined(_TP_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _TP_H

#include <lttng/tracepoint.h>
#include <uORB/topics/vehicle_land_detected.h>

TRACEPOINT_EVENT(
    land_detector,
    vehicle_land_detected,
    TP_ARGS(const struct vehicle_land_detected_s*, vehicle_land_detected),
    TP_FIELDS(
        ctf_float(float, alt_max, vehicle_land_detected->alt_max)
        ctf_integer(int, freefall, vehicle_land_detected->freefall)
        ctf_integer(int, ground_contact, vehicle_land_detected->ground_contact)
        ctf_integer(int, maybe_landed, vehicle_land_detected->maybe_landed)
        ctf_integer(int, landed, vehicle_land_detected->landed)
        ctf_integer(int, in_ground_effect, vehicle_land_detected->in_ground_effect)
    )
)

TRACEPOINT_EVENT(
    land_detector,
    takeoff_detected,
    TP_ARGS(),
    TP_FIELDS()
)

#endif /* _TP_H */

#include <lttng/tracepoint-event.h>
