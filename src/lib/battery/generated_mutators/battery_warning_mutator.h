/* Generated Modality mutator header file for 'BATTERY_WARNING_MUTATOR' */

#ifndef BATTERY_WARNING_MUTATOR_H
#define BATTERY_WARNING_MUTATOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const uint64_t HASH_BATTERY_WARNING_MUTATOR_warning_level;

extern void * const g_generated_state_BATTERY_WARNING_MUTATOR;

void mutate_BATTERY_WARNING_MUTATOR(
        modality_probe * const probe,
        void * const opaque_state,
        const uint64_t instrumentation_hash,
        void * const data,
        const size_t data_size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BATTERY_WARNING_MUTATOR_H */
