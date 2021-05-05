/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: vehicle-imu-component
 *   ID: dfa99a06-2d09-4d0b-a185-30812de2a8a4
 *   Code hash: a27f31626df05409d36afbadf63d8953bde123d8f4819330e6529bf431be2775
 *   Instrumentation hash: ebe7bbf89d33f29f35f341f4c7b96db961c9a98c646d13236f7ee6bc14b296bb
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 30b4b512dc9f8cb2fb53d8438eea90d639ef9dbfc1be031e700b827457e93c04)
 */

/*
 * Name: PX4_VEHICLE_IMU
 * Description: Vehicle IMU probe
 * Component ID: dfa99a06-2d09-4d0b-a185-30812de2a8a4
 * Tags: px4;library;vehicle-imu
 * Location: vehicle_imu/VehicleIMU.cpp:80
 */
#define PX4_VEHICLE_IMU (724167641UL)

/*
 * Events (sha3-256 a089f109842ef9d0c75020916e6f4da1ac9533c59603670b8df7b6d559798ff1)
 */

/*
 * Name: ACCEL_INTEGRATOR_READY
 * Description: Accelerometer integrator ready
 * Component ID: dfa99a06-2d09-4d0b-a185-30812de2a8a4
 * Tags: px4;vehicle-imu;accelerometer
 * Payload type: bool
 * Location: vehicle_imu/VehicleIMU.cpp:349
 */
#define ACCEL_INTEGRATOR_READY (1UL)

/*
 * Name: GYRO_INTEGRATOR_READY
 * Description: Gyroscope integrator ready
 * Component ID: dfa99a06-2d09-4d0b-a185-30812de2a8a4
 * Tags: px4;vehicle-imu;gyroscope
 * Payload type: bool
 * Location: vehicle_imu/VehicleIMU.cpp:357
 */
#define GYRO_INTEGRATOR_READY (2UL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
