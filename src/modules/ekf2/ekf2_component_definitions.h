/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: ekf2
 *   ID: 7e757c1d-7416-4b23-80fd-958294b055da
 *   Code hash: 7c11dc65e9a00ec3a07ff6cf90762b0bcc3cb67f89d1d40846a1450a5d533cdc
 *   Instrumentation hash: c34ffeb6886a1f1f42a88e7d21e2d2650a680cf7d4878cf7daa9aef84f51d09a
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 c991890b54f0a8a3cf83978d7eea22c99609a28319c0b3f8810d98fa1a586228)
 */

/*
 * Name: SENSOR_FUSION
 * Description: Sensor fusion probe
 * Component ID: 7e757c1d-7416-4b23-80fd-958294b055da
 * Tags: px4;module;ekf2
 * Location: ekf2/ekf2_main.cpp:673
 */
#define SENSOR_FUSION (134479735UL)

/*
 * Events (sha3-256 27bdc7b4d016d04196732c3718cd83a7b128d3749ef8150b633a307172ea8755)
 */

/*
 * Name: ROLL_ANGLE
 * Description: EKF2 estimated phi roll angle [radians]
 * Component ID: 7e757c1d-7416-4b23-80fd-958294b055da
 * Tags: px4;ekf2;time
 * Payload type: f32
 * Location: ekf2/ekf2_main.cpp:1899
 */
#define ROLL_ANGLE (1UL)

/*
 * Name: PITCH_ANGLE
 * Description: EKF2 estimated theta pitch angle [radians]
 * Component ID: 7e757c1d-7416-4b23-80fd-958294b055da
 * Tags: px4;ekf2;time
 * Payload type: f32
 * Location: ekf2/ekf2_main.cpp:1908
 */
#define PITCH_ANGLE (2UL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
