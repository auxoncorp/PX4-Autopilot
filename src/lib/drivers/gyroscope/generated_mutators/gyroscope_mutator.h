/* Generated Modality mutator header file for 'GYROSCOPE_MUTATOR' */

#ifndef GYROSCOPE_MUTATOR_H
#define GYROSCOPE_MUTATOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const uint64_t HASH_GYROSCOPE_MUTATOR_z_axis;

extern void * const g_generated_state_GYROSCOPE_MUTATOR;

void mutate_GYROSCOPE_MUTATOR(
        modality_probe * const probe,
        void * const opaque_state,
        const uint64_t instrumentation_hash,
        void * const data,
        const size_t data_size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* GYROSCOPE_MUTATOR_H */
