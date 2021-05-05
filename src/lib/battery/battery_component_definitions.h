/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: battery-component
 *   ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 *   Code hash: be145c0bb548db53edea73667e27386f3d36a793a10c0f2e8cc2bbca96350d76
 *   Instrumentation hash: 438cd722892386a6b9256fe642a12a57d66c572c5731fa44ba77e17a6bf4984a
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
 * Events (sha3-256 364d3fd5a778618fc5e7c51ebe5313034b4f4cfd714977d455e4242e45dd537b)
 */

/*
 * Name: STATE_RESET
 * Description: Battery reset it's state
 * Component ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 * Tags: px4;battery;power
 * Payload type:
 * Location: battery/battery.cpp:143
 */
#define STATE_RESET (1UL)

/*
 * Name: RAW_VOLTAGE
 * Description: Battery sampled raw voltage
 * Component ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 * Tags: px4;battery;power;time
 * Payload type: f32
 * Location: battery/battery.cpp:169
 */
#define RAW_VOLTAGE (2UL)

/*
 * Name: FILTERED_VOLTAGE
 * Description: Battery filtered voltage
 * Component ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 * Tags: px4;battery;voltage;power;time
 * Payload type: f32
 * Location: battery/battery.cpp:185
 */
#define FILTERED_VOLTAGE (3UL)

/*
 * Name: CONNECTED
 * Description: Battery connected state
 * Component ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 * Tags: px4;battery;power
 * Payload type: bool
 * Location: battery/battery.cpp:194
 */
#define CONNECTED (4UL)

/*
 * Name: WARNING_LEVEL
 * Description: Battery warning level
 * Component ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 * Tags: px4;battery;power
 * Payload type: u8
 * Location: battery/battery.cpp:223
 */
#define WARNING_LEVEL (5UL)

/*
 * Name: WARNING_LEVEL_OK
 * Description: Battery nominal voltage check
 * Component ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 * Tags: EXPECTATION;SEVERITY_8;px4;battery;power
 * Payload type: u32
 * Location: battery/battery.cpp:231
 */
#define WARNING_LEVEL_OK (6UL)

/*
 * Name: EMERGENCY_WARNING_LEVEL
 * Description: Battery emergency warning level
 * Component ID: f8b467f7-c6ea-495d-b7be-a4d008afb5ba
 * Tags: FAILURE;SEVERITY_10;px4;battery;power
 * Payload type:
 * Location: battery/battery.cpp:353
 */
#define EMERGENCY_WARNING_LEVEL (7UL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
