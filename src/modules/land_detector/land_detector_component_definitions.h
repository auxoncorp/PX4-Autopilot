/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: land-detector
 *   ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 *   Code hash: b32e1eff09672c7a8119f34ba734ee42fab8b3fead8b796a3909ad2a8e19c9dc
 *   Instrumentation hash: c3c91765ce7cc297b432d7e86c831e3d261863ae846e80748f5d15a0b20710a9
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 8c3ba0e3184661f9896dc19dec7e410994817207b9974886f71905a375d57857)
 */

/*
 * Name: LAND_DETECTOR
 * Description: Land detector probe
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;module;land-detector
 * Location: land_detector/LandDetector.cpp:56
 */
#define LAND_DETECTOR (433462535UL)

/*
 * Events (sha3-256 4c579b4925b588ff30ef3786261eb60b6125bedf93878c0fd05fd7ae799ba1b1)
 */

/*
 * Name: FREEFALL
 * Description: Freefall detection status
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;land-detector;freefall
 * Payload type: bool
 * Location: land_detector/LandDetector.cpp:149
 */
#define FREEFALL (1UL)

/*
 * Name: GROUND_CONTACT
 * Description: Ground contact detection status
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;land-detector
 * Payload type: bool
 * Location: land_detector/LandDetector.cpp:156
 */
#define GROUND_CONTACT (2UL)

/*
 * Name: MAYBE_LANDED
 * Description: Maybe landed detection status
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;land-detector
 * Payload type: bool
 * Location: land_detector/LandDetector.cpp:163
 */
#define MAYBE_LANDED (3UL)

/*
 * Name: LANDED
 * Description: Fused land detection status
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;land-detector
 * Payload type: bool
 * Location: land_detector/LandDetector.cpp:170
 */
#define LANDED (4UL)

/*
 * Name: TAKEOFF_DETECTED
 * Description: Takeoff detected
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;land-detector;takeoff
 * Payload type:
 * Location: land_detector/LandDetector.cpp:182
 */
#define TAKEOFF_DETECTED (5UL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
