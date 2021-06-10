/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: battery-component
 *   ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 *   Code hash: 066302afec5a02a0193e78317db18845f6f25e02f6d0a4b80a83fb3470d7fb91
 *   Instrumentation hash: d631af55b4e114cb933dd7ea5734c3f534fab58a5da728e7a196e940ad0ecd07
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 e8004c79e5143326196497d9007dff40924c24566b9f478b271911efc8956350)
 */

/*
 * Name: PX4_BATTERY
 * Description: Battery probe
 * Component ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 * Tags: px4;library;battery;power;control-plane
 * Location: battery/battery.cpp:114
 */
#define PX4_BATTERY (318704251UL)

/*
 * Events (sha3-256 4069ce3466c5db84db66c9d7646dbeb0f1d11ff1f08282d94450631fbbc2e904)
 */

/*
 * Name: STATE_RESET
 * Description: Battery reset it's state
 * Component ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 * Tags: px4;battery;power
 * Payload type:
 * Location: battery/battery.cpp:167
 */
#define STATE_RESET (1UL)

/*
 * Name: FILTERED_VOLTAGE
 * Description: Battery filtered voltage [volts]
 * Component ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 * Tags: px4;battery;voltage;power;time
 * Payload type: f32
 * Location: battery/battery.cpp:203
 */
#define FILTERED_VOLTAGE (2UL)

/*
 * Name: WARNING_LEVEL
 * Description: Battery warning level
 * Component ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 * Tags: px4;battery;power
 * Payload type: u8
 * Location: battery/battery.cpp:234
 */
#define WARNING_LEVEL (3UL)

/*
 * Name: EMERGENCY_WARNING_LEVEL
 * Description: Battery emergency warning level
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
