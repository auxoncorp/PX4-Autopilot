/* Generated Modality mutator implementation for 'GYROSCOPE_MUTATOR' */

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
    float z_axis;
} g_generated_state_s;

static g_generated_state_s g_generated_state =
{
    .is_registered = false,
    .is_injected = false,
    .z_axis = 0.0f,
};

void * const g_generated_state_GYROSCOPE_MUTATOR = &g_generated_state;

static const char *TAGS_GYROSCOPE_MUTATOR[2] =
{
    "gyroscope",
    "px4",
};

static const modality_mutation_parameter_definition PARAM_DEFS_GYROSCOPE_MUTATOR[1] =
{
    [0] =
    {
        .param_type =
        {
            .tag = MUTATION_PARAM_TYPE_F32,
            .body.f32 =
            {
                .minimum_effect_value = 0.0f,
                .nominal_range = { .inclusive_start = -34.90659f, .inclusive_end = 34.90659f },
                .safety_range = { .inclusive_start = -34.90659f, .inclusive_end = 34.90659f },
                .hard_range = { .inclusive_start = -34.90659f, .inclusive_end = 34.90659f },
            },
        },
        .name = "z-axis",
    },
};

const uint64_t HASH_GYROSCOPE_MUTATOR_z_axis = 5183317293488150476ULL;

static const modality_mutation_definition MUTATOR_DEF_GYROSCOPE_MUTATOR =
{
    .name = "gyroscope-mutator",
    .params = PARAM_DEFS_GYROSCOPE_MUTATOR,
    .params_length = 1,
    .tags = TAGS_GYROSCOPE_MUTATOR,
    .tags_length = 2,
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
    (*definition) = &MUTATOR_DEF_GYROSCOPE_MUTATOR;
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

    assert(params[0].tag == MUTATION_PARAM_F32);
    state->z_axis = params[0].body.f32.value;

    state->is_injected = true;
    return 0;
}

static const modality_mutation_interface GYROSCOPE_MUTATOR =
{
    .state = (void*) &g_generated_state,
    .inject_mutation = &inject_mutation,
    .get_definition = &get_definition,
    .clear_mutations = &clear_mutations,
};

void mutate_GYROSCOPE_MUTATOR(
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
                &GYROSCOPE_MUTATOR);
        assert(err == MODALITY_PROBE_ERROR_OK);
    }

    if(state->is_injected == true)
    {
        if(instrumentation_hash == HASH_GYROSCOPE_MUTATOR_z_axis)
        {
            assert(data_size == sizeof(state->z_axis));
            (void) memcpy(data, &state->z_axis, data_size);
        }
        else
        {
            assert(false); /* Got an unrecognized hash */
        }
    }
}
