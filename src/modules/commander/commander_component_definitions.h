/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: commander
 *   ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 *   Code hash: 22e24ea820912732ba5f40751b360771b63c05cc34a720825f84719d852fd1b0
 *   Instrumentation hash: 96c266a7e192cc04174359227d14e39eb54846d41cf4b5e3d2b3f080b6fc0b9d
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 88424cac9b8c9f07a4bc6d8f850f3d45571b5d3d7825cf886e29b5a0a73d19f2)
 */

/*
 * Name: COMMANDER
 * Description: Commander probe
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;module;commander
 * Location: commander/Commander.cpp:534
 */
#define COMMANDER (483644201UL)

/*
 * Events (sha3-256 a9b093428ef9a2a86a2dfd4b82ac78a7f97d79504f69bd339fd8720b22a5ca77)
 */

/*
 * Name: LAND_DETECTED
 * Description: Landing detected
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
 * Description: Entering lockdown due to a critical failure
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_10;px4;commander;failure-detector;time
 * Payload type:
 * Location: commander/Commander.cpp:2317
 */
#define LOCKDOWN_TRIGGERED (3UL)

/*
 * Name: FLIGHT_TERMINATED
 * Description: Terminating flight due to a critical failure
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_10;px4;commander;failure-detector;time
 * Payload type:
 * Location: commander/Commander.cpp:2336
 */
#define FLIGHT_TERMINATED (4UL)

/*
 * Name: BATTERY_WARNING_LEVEL
 * Description: Battery warning level received
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
 * Description: Failure detector reset the attitude status
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;failure-detector
 * Payload type: bool
 * Location: commander/failure_detector/FailureDetector.cpp:64
 */
#define FAILURE_DETECTOR_RESET_ATTITUDE_STATUS (7UL)

/*
 * Name: FAILURE_DETECTOR_UPDATED
 * Description: Failure detector state updated
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;failure-detector
 * Payload type: bool
 * Location: commander/failure_detector/FailureDetector.cpp:100
 */
#define FAILURE_DETECTOR_UPDATED (8UL)

/*
 * Name: FAILURE_DETECTOR_ATTITUDE_STABLE
 * Description: Updated the failure detector attitude stabilized status
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;failure-detector;time
 * Payload type: bool
 * Location: commander/failure_detector/FailureDetector.cpp:128
 */
#define FAILURE_DETECTOR_ATTITUDE_STABLE (9UL)

/*
 * Name: FAILURE_DETECTOR_STATUS_ROLL_ASSERTED
 * Description: Failure detector roll failure asserted
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: EXPECTATION;SEVERITY_10;px4;commander;failure-detector;time
 * Payload type: u32
 * Location: commander/failure_detector/FailureDetector.cpp:185
 */
#define FAILURE_DETECTOR_STATUS_ROLL_ASSERTED (10UL)

/*
 * Name: FAILURE_DETECTOR_STATUS_PITCH_ASSERTED
 * Description: Failure detector pitch failure asserted
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: EXPECTATION;SEVERITY_10;px4;commander;failure-detector;time
 * Payload type: u32
 * Location: commander/failure_detector/FailureDetector.cpp:195
 */
#define FAILURE_DETECTOR_STATUS_PITCH_ASSERTED (11UL)

/*
 * Name: LOW_BATTERY_RETURN_ADVISED
 * Description: Return advised due to low battery level
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1005
 */
#define LOW_BATTERY_RETURN_ADVISED (12UL)

/*
 * Name: CRITICAL_BATTERY_LEVEL
 * Description: Critical battery level detected
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1014
 */
#define CRITICAL_BATTERY_LEVEL (13UL)

/*
 * Name: CRITICAL_BATTERY_LANDING_ADVISED
 * Description: Landing advised due to critical battery level
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_7;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1026
 */
#define CRITICAL_BATTERY_LANDING_ADVISED (14UL)

/*
 * Name: CRITICAL_BATTERY_RTL
 * Description: Return-to-landing due to critical battery level
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_8;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1044
 */
#define CRITICAL_BATTERY_RTL (15UL)

/*
 * Name: CRITICAL_BATTERY_RTL_FALLBACK_LANDING
 * Description: Landing now instead of RTL due to critical battery level
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_8;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1056
 */
#define CRITICAL_BATTERY_RTL_FALLBACK_LANDING (16UL)

/*
 * Name: CRITICAL_BATTERY_LANDING
 * Description: Landing due to critical battery level
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_8;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1071
 */
#define CRITICAL_BATTERY_LANDING (17UL)

/*
 * Name: EMERGENCY_BATTERY_LEVEL
 * Description: Taking action due to emergency battery level
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1085
 */
#define EMERGENCY_BATTERY_LEVEL (18UL)

/*
 * Name: EMERGENCY_BATTERY_LANDING_ADVISED
 * Description: Landing advised due to emergency battery level
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_9;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1097
 */
#define EMERGENCY_BATTERY_LANDING_ADVISED (19UL)

/*
 * Name: EMERGENCY_BATTERY_RTL
 * Description: Return-to-landing due to emergency battery level
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_9;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1111
 */
#define EMERGENCY_BATTERY_RTL (20UL)

/*
 * Name: EMERGENCY_BATTERY_RTL_FALLBACK_LANDING
 * Description: Landing now instead of RTL due to emergency battery level
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_9;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1123
 */
#define EMERGENCY_BATTERY_RTL_FALLBACK_LANDING (21UL)

/*
 * Name: EMERGENCY_BATTERY_LANDING
 * Description: Landing due to emergency battery level
 * Component ID: 31e0c252-5a6a-43fd-965a-40bd5556c257
 * Tags: FAILURE;SEVERITY_9;px4;commander;battery
 * Payload type:
 * Location: commander/state_machine_helper.cpp:1141
 */
#define EMERGENCY_BATTERY_LANDING (22UL)

/*
 * Name: BATTERY_FAILURE_DETECTED
 * Description: A failure with the battery was detected
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
