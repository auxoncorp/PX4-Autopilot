/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: land-detector-component
 *   ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 *   Code hash: 7f2beaf3877a20bf8b5ea1f7ae2e8a755a2847c061da3cbf01c97e140e7e324b
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
 * Events (sha3-256 5ecf2cfca0b4ab40f7cf8ce06e739cbb6a77abb63b34b93e029e57264ae6156b)
 */

/*
 * Name: FREEFALL
 * Description: Land detector freefall
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;land-detector;freefall
 * Payload type: bool
 * Location: land_detector/LandDetector.cpp:149
 */
#define FREEFALL (1UL)

/*
 * Name: GROUND_CONTACT
 * Description: Land detector ground contact
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;land-detector
 * Payload type: bool
 * Location: land_detector/LandDetector.cpp:156
 */
#define GROUND_CONTACT (2UL)

/*
 * Name: MAYBE_LANDED
 * Description: Land detector might have landed
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;land-detector
 * Payload type: bool
 * Location: land_detector/LandDetector.cpp:163
 */
#define MAYBE_LANDED (3UL)

/*
 * Name: LANDED
 * Description: Land detector currently landed (stage 3)
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;land-detector
 * Payload type: bool
 * Location: land_detector/LandDetector.cpp:170
 */
#define LANDED (4UL)

/*
 * Name: TAKE_OFF_DETECTED
 * Description: Take off detected
 * Component ID: a3d31cc0-c05d-4653-a225-32f29eec463f
 * Tags: px4;land-detector;takeoff
 * Payload type:
 * Location: land_detector/LandDetector.cpp:182
 */
#define TAKE_OFF_DETECTED (5UL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
