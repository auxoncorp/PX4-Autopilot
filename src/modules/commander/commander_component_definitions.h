/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: commander-component
 *   ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 *   Code hash: e9b391e211314466235de2515c782fa94f090e184fe26ccf892568417481907f
 *   Instrumentation hash: 19a2bd9a36af2dedf6f444d7293b24593b7204327d9263241cf18f6220221b3c
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 86027f0683bce98867060de5734b1524d02252d9532a85e397a022ac85856639)
 */

/*
 * Name: PX4_COMMANDER
 * Description: Commander probe
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;module;commander
 * Location: commander/Commander.cpp:534
 */
#define PX4_COMMANDER (483644201UL)

/*
 * Events (sha3-256 44e3f44adb2356fcfc260d158fc7447e4e6e007090d683d512e3d76208e35dd3)
 */

/*
 * Name: LAND_DETECTED
 * Description: Land detected
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander
 * Payload type:
 * Location: commander/Commander.cpp:1677
 */
#define LAND_DETECTED (1UL)

/*
 * Name: TAKEOFF_DETECTED
 * Description: Takeoff detected
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander
 * Payload type:
 * Location: commander/Commander.cpp:1695
 */
#define TAKEOFF_DETECTED (2UL)

/*
 * Name: LOCKDOWN_TRIGGERED
 * Description: Critical failure detected: lockdown
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_10;px4;commander;failure-detector;time
 * Payload type:
 * Location: commander/Commander.cpp:2317
 */
#define LOCKDOWN_TRIGGERED (3UL)

/*
 * Name: FLIGHT_TERMINATED
 * Description: Critical failure detected: terminate flight
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_10;px4;commander;failure-detector;time
 * Payload type:
 * Location: commander/Commander.cpp:2336
 */
#define FLIGHT_TERMINATED (4UL)

/*
 * Name: BATTERY_WARNING_LEVEL
 * Description: Battery warn level received
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;battery;power
 * Payload type: u8
 * Location: commander/Commander.cpp:4108
 */
#define BATTERY_WARNING_LEVEL (5UL)

/*
 * Name: BATTERY_WARNING_LEVEL_INCREASED_WHILE_ARMED
 * Description: Battery warning level increased while armed
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;battery;power
 * Payload type:
 * Location: commander/Commander.cpp:4116
 */
#define BATTERY_WARNING_LEVEL_INCREASED_WHILE_ARMED (6UL)

/*
 * Name: FAILURE_DETECTOR_RESET_ATTITUDE_STATUS
 * Description: Failure detector reset attitude status
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;failure-detector
 * Payload type: bool
 * Location: commander/failure_detector/FailureDetector.cpp:64
 */
#define FAILURE_DETECTOR_RESET_ATTITUDE_STATUS (7UL)

/*
 * Name: FAILURE_DETECTOR_UPDATED
 * Description: Failure detector updated
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;failure-detector
 * Payload type: bool
 * Location: commander/failure_detector/FailureDetector.cpp:100
 */
#define FAILURE_DETECTOR_UPDATED (8UL)

/*
 * Name: FAILURE_DETECTOR_ATTITUDE_STABLE
 * Description: Failure detector attitude stabilized updated
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;failure-detector;time
 * Payload type: bool
 * Location: commander/failure_detector/FailureDetector.cpp:128
 */
#define FAILURE_DETECTOR_ATTITUDE_STABLE (9UL)

/*
 * Name: FAILURE_DETECTOR_STATUS_ROLL_ASSERTED
 * Description: Failure detector status roll asserted
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: EXPECTATION;SEVERITY_10;px4;commander;failure-detector;time
 * Payload type: u32
 * Location: commander/failure_detector/FailureDetector.cpp:185
 */
#define FAILURE_DETECTOR_STATUS_ROLL_ASSERTED (10UL)

/*
 * Name: FAILURE_DETECTOR_STATUS_PITCH_ASSERTED
 * Description: Failure detector status pitch asserted
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: EXPECTATION;SEVERITY_10;px4;commander;failure-detector;time
 * Payload type: u32
 * Location: commander/failure_detector/FailureDetector.cpp:195
 */
#define FAILURE_DETECTOR_STATUS_PITCH_ASSERTED (11UL)

/*
 * Name: LOW_BATTERY_RETURN_ADVISED
 * Description: Low battery level return advised
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1005
 */
#define LOW_BATTERY_RETURN_ADVISED (12UL)

/*
 * Name: CRITICAL_BATTERY_LEVEL
 * Description: Critical battery level
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1014
 */
#define CRITICAL_BATTERY_LEVEL (13UL)

/*
 * Name: CRITICAL_BATTERY_LANDING_ADVISED
 * Description: Critical battery level landing advised
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_7;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1026
 */
#define CRITICAL_BATTERY_LANDING_ADVISED (14UL)

/*
 * Name: CRITICAL_BATTERY_RTL
 * Description: Critical battery level RTL
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_8;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1044
 */
#define CRITICAL_BATTERY_RTL (15UL)

/*
 * Name: CRITICAL_BATTERY_RTL_FALLBACK_LANDING
 * Description: Critical battery level landing instead of RTL
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_8;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1056
 */
#define CRITICAL_BATTERY_RTL_FALLBACK_LANDING (16UL)

/*
 * Name: CRITICAL_BATTERY_LANDING
 * Description: Critical battery level landing
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_8;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1071
 */
#define CRITICAL_BATTERY_LANDING (17UL)

/*
 * Name: EMERGENCY_BATTERY_LEVEL
 * Description: Emergency battery level
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1085
 */
#define EMERGENCY_BATTERY_LEVEL (18UL)

/*
 * Name: EMERGENCY_BATTERY_LANDING_ADVISED
 * Description: Emergency battery level landing advised
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_9;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1097
 */
#define EMERGENCY_BATTERY_LANDING_ADVISED (19UL)

/*
 * Name: EMERGENCY_BATTERY_RTL
 * Description: Emergency battery level RTL
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_9;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1111
 */
#define EMERGENCY_BATTERY_RTL (20UL)

/*
 * Name: EMERGENCY_BATTERY_RTL_FALLBACK_LANDING
 * Description: Emergency battery level landing instead of RTL
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_9;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1123
 */
#define EMERGENCY_BATTERY_RTL_FALLBACK_LANDING (21UL)

/*
 * Name: EMERGENCY_BATTERY_LANDING
 * Description: Emergency battery level landing
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_9;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1141
 */
#define EMERGENCY_BATTERY_LANDING (22UL)

/*
 * Name: BATTERY_FAILURE_DETECTED
 * Description: Battery failure detected
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_10;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1156
 */
#define BATTERY_FAILURE_DETECTED (23UL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
