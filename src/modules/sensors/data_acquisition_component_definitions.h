/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: data-acquisition
 *   ID: 81e416a3-7250-47d4-9c24-3b6f1c6fbcdc
 *   Code hash: cfbfb5bab3358c58698bce0550fa5daffd05311eeb4d33dfff1d2d72597798b3
 *   Instrumentation hash: c45620deee3706100f4d767ceac183fe6917c5cb6bbd2ca5f80ea153c99564ab
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 3696b429b506c9b9de2a02fa01fb9d770082c62c80598a2ed18c39c1a82a2ff9)
 */

/*
 * Name: SENSORS
 * Description: Sensors probe
 * Component ID: 81e416a3-7250-47d4-9c24-3b6f1c6fbcdc
 * Tags: px4;module;sensors
 * Location: sensors/sensors.cpp:242
 */
#define SENSORS (213414513UL)

/*
 * Name: VEHICLE_IMU
 * Description: Vehicle IMU probe
 * Component ID: 81e416a3-7250-47d4-9c24-3b6f1c6fbcdc
 * Tags: px4;library;vehicle-imu
 * Location: sensors/vehicle_imu/VehicleIMU.cpp:80
 */
#define VEHICLE_IMU (724167641UL)

/*
 * Events (sha3-256 0482095cf5d9163a900c6dbbe0c11080ad3b64e301a655740885a1c8a06e8f4d)
 */

/*
 * Name: SENSORS_POLLED
 * Description: Combined sensors polled
 * Component ID: 81e416a3-7250-47d4-9c24-3b6f1c6fbcdc
 * Tags: px4;sensors
 * Payload type:
 * Location: sensors/sensors.cpp:584
 */
#define SENSORS_POLLED (1UL)

/*
 * Name: GYRO_INTEGRATOR_READY
 * Description: Vehicle IMU gyroscope integrator ready status
 * Component ID: 81e416a3-7250-47d4-9c24-3b6f1c6fbcdc
 * Tags: px4;vehicle-imu;gyroscope
 * Payload type: bool
 * Location: sensors/vehicle_imu/VehicleIMU.cpp:357
 */
#define GYRO_INTEGRATOR_READY (2UL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
