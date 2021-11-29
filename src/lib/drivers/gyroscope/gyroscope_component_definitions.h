/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: gyroscope
 *   ID: 6779bbe8-b7eb-447c-b4b5-56a9d7c00aa2
 *   Code hash: 05f6ff26955cf85f6c6c18feb5e1b31fa188dac15839598a0a8d8c006f1e2359
 *   Instrumentation hash: 862256b7ea9605d61f130d54c7103bf23d96d9326f00851c9bad2414792f303a
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 8e913e67123333b94824093e1dbaeab9dfddfbf625f885a21ae9fc7f69dd2aa0)
 */

/*
 * Name: GYROSCOPE
 * Description: Gyroscope probe
 * Component ID: 6779bbe8-b7eb-447c-b4b5-56a9d7c00aa2
 * Tags: px4;library;gyroscope;sensor;control-plane
 * Location: gyroscope/PX4Gyroscope.cpp:74
 */
#define GYROSCOPE (441590204UL)

/*
 * Events (sha3-256 5b0733f71dd691759f2d9482630c45b6645939fc6f04671184938e9831272eb3)
 */

/*
 * Name: ROLL_ANGULAR_RATE
 * Description: Gyroscope x axis roll angular rate [radians/second]
 * Component ID: 6779bbe8-b7eb-447c-b4b5-56a9d7c00aa2
 * Tags: px4;gyroscope;sensor;time
 * Payload type: f32
 * Location: gyroscope/PX4Gyroscope.cpp:217
 */
#define ROLL_ANGULAR_RATE (1UL)

/*
 * Name: PITCH_ANGULAR_RATE
 * Description: Gyroscope y axis pitch angular rate [radians/second]
 * Component ID: 6779bbe8-b7eb-447c-b4b5-56a9d7c00aa2
 * Tags: px4;gyroscope;sensor;time
 * Payload type: f32
 * Location: gyroscope/PX4Gyroscope.cpp:225
 */
#define PITCH_ANGULAR_RATE (2UL)

/*
 * Name: YAW_ANGULAR_RATE
 * Description: Gyroscope z axis yaw angular rate [radians/second]
 * Component ID: 6779bbe8-b7eb-447c-b4b5-56a9d7c00aa2
 * Tags: px4;gyroscope;sensor;time
 * Payload type: f32
 * Location: gyroscope/PX4Gyroscope.cpp:233
 */
#define YAW_ANGULAR_RATE (3UL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
