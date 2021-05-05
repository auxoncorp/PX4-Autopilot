/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: land-detector-component
 *   ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 *   Code hash: 0c3a54aef73c14c640fbd8758093dd5656ff6a3692ef4aa35941aa4bc4fe955c
 *   Instrumentation hash: 11cd3fe8d11560297b044e7961ef14e8b2a36432eccb005b701bb90910009e3b
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 ca179e21d96ec42f357ee523e4022d774da925a1d48ac0095f4cd759ed0e3d33)
 */

/*
 * Name: PX4_LAND_DETECTOR
 * Description: Land detector probe
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;module;land-detector
 * Location: land_detector/LandDetector.cpp:56
 */
#define PX4_LAND_DETECTOR (433462535UL)

/*
 * Events (sha3-256 96c284e475a2f7ef6c7bfd7d77ea561598bb522e0e6c8328f70e5e703225ed5f)
 */

/*
 * Name: FREEFALL
 * Description: Land detector freefall
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;land-detector;freefall
 * Payload type: bool
 * Location: land_detector/LandDetector.cpp:132
 */
#define FREEFALL (1UL)

/*
 * Name: GROUND_CONTACT
 * Description: Land detector ground contact
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;land-detector
 * Payload type: bool
 * Location: land_detector/LandDetector.cpp:139
 */
#define GROUND_CONTACT (2UL)

/*
 * Name: MAYBE_LANDED
 * Description: Land detector might have landed
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;land-detector
 * Payload type: bool
 * Location: land_detector/LandDetector.cpp:146
 */
#define MAYBE_LANDED (3UL)

/*
 * Name: LANDED
 * Description: Land detector currently landed (stage 3)
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;land-detector
 * Payload type: bool
 * Location: land_detector/LandDetector.cpp:153
 */
#define LANDED (4UL)

/*
 * Name: TAKE_OFF_DETECTED
 * Description: Take off detected
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;land-detector;takeoff
 * Payload type:
 * Location: land_detector/LandDetector.cpp:174
 */
#define TAKE_OFF_DETECTED (5UL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
