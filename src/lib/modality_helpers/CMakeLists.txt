# Keep asserts
add_definitions(-UNDEBUG)

px4_add_library(modality_helpers modality_helpers.cpp)

# Implement persistent epoch sequence id as text files in the build directory
# In the root, rather than under the PX4_CONFIG subdir so that switching between configs can retain the state
target_compile_definitions(
    modality_helpers
    PRIVATE MODALITY_PERSISTENT_EPOCH_CACHE_DIR="${CMAKE_SOURCE_DIR}/build/persistent_epoch_cache"
    )

# Modality library will be transitive, linking this target will also link libmodality_probe
target_link_libraries(modality_helpers PUBLIC ModalityProbe::LibModalityProbe)

target_include_directories(
    modality_helpers
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    )
