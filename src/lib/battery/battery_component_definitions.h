/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: battery
 *   ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 *   Code hash: e10b86f8d43fb5869a7e1d94ea39b56d558ade0bd05ea3bcf6a4d3f1624b6a80
 *   Instrumentation hash: 68b60c3982da07a1d71ca8070413d36fc95bad5678e2759d77a9ec56195b8a98
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 8476f50b0f7c93a9600897da2ccf91938e6ea1ffcec5f40542dd802646beb61a)
 */

/*
 * Name: BATTERY
 * Description: Battery and power management probe
 * Component ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 * Tags: px4;library;battery;power;control-plane
 * Location: battery/battery.cpp:114
 */
#define BATTERY (318704251UL)

/*
 * Events (sha3-256 f69e7046ead25491659c16f27ad4e387e3780cd7ad6cfe8622a7925b77060e7e)
 */

/*
 * Name: STATE_RESET
 * Description: Battery filters and monitoring state reset
 * Component ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 * Tags: px4;battery;power
 * Payload type:
 * Location: battery/battery.cpp:167
 */
#define STATE_RESET (1UL)

/*
 * Name: FILTERED_VOLTAGE
 * Description: Post-filter battery voltage [volts]
 * Component ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 * Tags: px4;battery;voltage;power;time
 * Payload type: f32
 * Location: battery/battery.cpp:203
 */
#define FILTERED_VOLTAGE (2UL)

/*
 * Name: WARNING_LEVEL
 * Description: Battery voltage warning level
 * Component ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 * Tags: px4;battery;power
 * Payload type: u8
 * Location: battery/battery.cpp:234
 */
#define WARNING_LEVEL (3UL)

/*
 * Name: EMERGENCY_WARNING_LEVEL
 * Description: Battery warning level has reached the emergency threshold
 * Component ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 * Tags: FAILURE;SEVERITY_10;px4;battery;power
 * Payload type:
 * Location: battery/battery.cpp:371
 */
#define EMERGENCY_WARNING_LEVEL (4UL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
