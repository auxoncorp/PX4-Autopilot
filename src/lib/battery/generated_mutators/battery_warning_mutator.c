/* Generated Modality mutator implementation for 'BATTERY_WARNING_MUTATOR' */

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "modality/probe.h"
#include "modality/mutation_interface.h"

void *memcpy(void *dest, const void *src, size_t n);

typedef struct g_generated_state_s
{
    bool is_registered;
    bool is_injected;
    int32_t warning_level;
} g_generated_state_s;

static g_generated_state_s g_generated_state =
{
    .is_registered = false,
    .is_injected = false,
    .warning_level = 0,
};

void * const g_generated_state_BATTERY_WARNING_MUTATOR = &g_generated_state;

static const char *TAGS_BATTERY_WARNING_MUTATOR[3] =
{
    "battery",
    "power",
    "px4",
};

static const modality_mutation_option_value_and_name VALUES_AND_NAMES_WARNING_LEVEL[5] =
{
[0] = { 0, "NONE" },
[1] = { 1, "LOW" },
[2] = { 2, "CRITICAL" },
[3] = { 3, "EMERGENCY" },
[4] = { 4, "FAILED" },
};

static const modality_mutation_parameter_definition PARAM_DEFS_BATTERY_WARNING_MUTATOR[1] =
{
    [0] =
    {
        .param_type =
        {
            .tag = MUTATION_PARAM_TYPE_ENUM,
            .body.enumeration =
            {
                .option_values_and_names = VALUES_AND_NAMES_WARNING_LEVEL,
                .option_values_and_names_length = 5,
                .constraints =
                {
                    .minimum_effect_value = 0,
                    .nominal_range = { .inclusive_start = 0, .inclusive_end = 4 },
                    .safety_range = { .inclusive_start = 0, .inclusive_end = 4 },
                    .hard_range = { .inclusive_start = 0, .inclusive_end = 4 },
                },
            },
        },
        .name = "warning-level",
    },
};

const uint64_t HASH_BATTERY_WARNING_MUTATOR_warning_level = 9834462897820421572ULL;

static const modality_mutation_definition MUTATOR_DEF_BATTERY_WARNING_MUTATOR =
{
    .name = "battery-warning-mutator",
    .params = PARAM_DEFS_BATTERY_WARNING_MUTATOR,
    .params_length = 1,
    .tags = TAGS_BATTERY_WARNING_MUTATOR,
    .tags_length = 3,
};

static size_t clear_mutations(
        void * const fi)
{
    assert(fi != NULL);
    g_generated_state_s * const state = (g_generated_state_s*) fi;
    state->is_injected = false;
    return 0;
}

static size_t get_definition(
        void * const fi,
        const modality_mutation_definition ** const definition)
{
    assert(fi != NULL);
    (*definition) = &MUTATOR_DEF_BATTERY_WARNING_MUTATOR;
    return 0;
}

static size_t inject_mutation(
        void * const fi,
        const modality_mutation_param * const params,
        const size_t params_length)
{
    assert(fi != NULL);
    g_generated_state_s * const state = (g_generated_state_s*) fi;
    assert(params != NULL);
    assert(params_length == 1);

    assert(params[0].tag == MUTATION_PARAM_ENUM_SELECTION);
    state->warning_level = params[0].body.enum_selection.value;

    state->is_injected = true;
    return 0;
}

static const modality_mutation_interface BATTERY_WARNING_MUTATOR =
{
    .state = (void*) &g_generated_state,
    .inject_mutation = &inject_mutation,
    .get_definition = &get_definition,
    .clear_mutations = &clear_mutations,
};

void mutate_BATTERY_WARNING_MUTATOR(
        modality_probe * const probe,
        void * const opaque_state,
        const uint64_t instrumentation_hash,
        void * const data,
        const size_t data_size)
{
    assert(probe != NULL);
    assert(opaque_state != NULL);
    assert(instrumentation_hash != 0);
    assert(data != NULL);
    assert(data_size != 0);

    g_generated_state_s * const state = (g_generated_state_s*) opaque_state;
    assert(state == &g_generated_state);

    if(state->is_registered == false)
    {
        state->is_registered = true;

        const size_t err = modality_probe_register_mutator(
                probe,
                &BATTERY_WARNING_MUTATOR);
        assert(err == MODALITY_PROBE_ERROR_OK);
    }

    if(state->is_injected == true)
    {
        if(instrumentation_hash == HASH_BATTERY_WARNING_MUTATOR_warning_level)
        {
            assert(data_size == sizeof(state->warning_level));
            (void) memcpy(data, &state->warning_level, data_size);
        }
        else
        {
            assert(false); /* Got an unrecognized hash */
        }
    }
}
