/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: commander-component
 *   ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 *   Code hash: a9cf656060b6d77c59cb9bd169c61feed745888f70c5d32d0e07b4687aabc9a1
 *   Instrumentation hash: f0c881755dd818d38cf54dbf4f1add3d62f90d605fa3511027340cee6eb3c3e3
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 f492231e45385ddf5a2cea99c98a292d9e8113b3e924df8dd441c527048917f5)
 */

/*
 * Name: PX4_COMMANDER
 * Description: Commander probe
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;module;commander
 * Location: commander/Commander.cpp:533
 */
#define PX4_COMMANDER (828891432UL)

/*
 * Events (sha3-256 4dbd8216adde3b0c16aea5496286ae4c9c879cfdc47cce6060313927309b4223)
 */

/*
 * Name: LAND_DETECTED
 * Description: Land detected
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander
 * Payload type:
 * Location: commander/Commander.cpp:1667
 */
#define LAND_DETECTED (1UL)

/*
 * Name: TAKEOFF_DETECTED
 * Description: Takeoff detected
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander
 * Payload type:
 * Location: commander/Commander.cpp:1685
 */
#define TAKEOFF_DETECTED (2UL)

/*
 * Name: BATTERY_WARNING_LEVEL
 * Description: Battery warn level received
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;battery;power
 * Payload type: u8
 * Location: commander/Commander.cpp:4073
 */
#define BATTERY_WARNING_LEVEL (3UL)

/*
 * Name: BATTERY_WARNING_LEVEL_INCREASED_WHILE_ARMED
 * Description: Battery warning level increased while armed
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;battery;power
 * Payload type: bool
 * Location: commander/Commander.cpp:4081
 */
#define BATTERY_WARNING_LEVEL_INCREASED_WHILE_ARMED (4UL)

/*
 * Name: FAILURE_DETECTOR_RESET_ATTITUDE_STATUS
 * Description: Failure detector reset attitude status
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;failure-detector
 * Payload type: bool
 * Location: commander/failure_detector/FailureDetector.cpp:64
 */
#define FAILURE_DETECTOR_RESET_ATTITUDE_STATUS (5UL)

/*
 * Name: FAILURE_DETECTOR_UPDATED
 * Description: Failure detector updated
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;failure-detector
 * Payload type: bool
 * Location: commander/failure_detector/FailureDetector.cpp:100
 */
#define FAILURE_DETECTOR_UPDATED (6UL)

/*
 * Name: FAILURE_DETECTOR_ATTITUDE_STABLE
 * Description: Failure detector attitude stabilized updated
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;failure-detector;time
 * Payload type: bool
 * Location: commander/failure_detector/FailureDetector.cpp:128
 */
#define FAILURE_DETECTOR_ATTITUDE_STABLE (7UL)

/*
 * Name: FAILURE_DETECTOR_STATUS_ROLL_ASSERTED
 * Description: Failure detector status roll asserted
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: EXPECTATION;SEVERITY_10;px4;commander;failure-detector;time
 * Payload type: u32
 * Location: commander/failure_detector/FailureDetector.cpp:185
 */
#define FAILURE_DETECTOR_STATUS_ROLL_ASSERTED (8UL)

/*
 * Name: FAILURE_DETECTOR_STATUS_PITCH_ASSERTED
 * Description: Failure detector status pitch asserted
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: EXPECTATION;SEVERITY_10;px4;commander;failure-detector;time
 * Payload type: u32
 * Location: commander/failure_detector/FailureDetector.cpp:195
 */
#define FAILURE_DETECTOR_STATUS_PITCH_ASSERTED (9UL)

/*
 * Name: LOW_BATTERY_RETURN_ADVISED
 * Description: Low battery level return advised
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1005
 */
#define LOW_BATTERY_RETURN_ADVISED (10UL)

/*
 * Name: CRITICAL_BATTERY_LEVEL
 * Description: Critical battery level
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1014
 */
#define CRITICAL_BATTERY_LEVEL (11UL)

/*
 * Name: CRITICAL_BATTERY_LANDING_ADVISED
 * Description: Critical battery level landing advised
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_7;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1026
 */
#define CRITICAL_BATTERY_LANDING_ADVISED (12UL)

/*
 * Name: CRITICAL_BATTERY_RTL
 * Description: Critical battery level RTL
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_8;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1044
 */
#define CRITICAL_BATTERY_RTL (13UL)

/*
 * Name: CRITICAL_BATTERY_RTL_FALLBACK_LANDING
 * Description: Critical battery level landing instead of RTL
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_8;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1056
 */
#define CRITICAL_BATTERY_RTL_FALLBACK_LANDING (14UL)

/*
 * Name: CRITICAL_BATTERY_LANDING
 * Description: Critical battery level landing
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_8;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1071
 */
#define CRITICAL_BATTERY_LANDING (15UL)

/*
 * Name: EMERGENCY_BATTERY_LEVEL
 * Description: Emergency battery level
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1085
 */
#define EMERGENCY_BATTERY_LEVEL (16UL)

/*
 * Name: EMERGENCY_BATTERY_LANDING_ADVISED
 * Description: Emergency battery level landing advised
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_9;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1097
 */
#define EMERGENCY_BATTERY_LANDING_ADVISED (17UL)

/*
 * Name: EMERGENCY_BATTERY_RTL
 * Description: Emergency battery level RTL
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_9;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1111
 */
#define EMERGENCY_BATTERY_RTL (18UL)

/*
 * Name: EMERGENCY_BATTERY_RTL_FALLBACK_LANDING
 * Description: Emergency battery level landing instead of RTL
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_9;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1123
 */
#define EMERGENCY_BATTERY_RTL_FALLBACK_LANDING (19UL)

/*
 * Name: EMERGENCY_BATTERY_LANDING
 * Description: Emergency battery level landing
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_9;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1141
 */
#define EMERGENCY_BATTERY_LANDING (20UL)

/*
 * Name: BATTERY_FAILURE_DETECTED
 * Description: Battery failure detected
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_10;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1156
 */
#define BATTERY_FAILURE_DETECTED (21UL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
