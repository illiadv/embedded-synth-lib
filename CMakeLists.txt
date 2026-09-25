cmake_minimum_required(VERSION 3.15)
project(embedded_synth_lib VERSION 1.0.0 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(synth
    src/wt_trunc.c
    src/wt_lerp.c
    src/wt.c

    src/fm_lut.c
    src/fm_sin.c
)

target_include_directories(synth PRIVATE ${INCLUDES})


# Tests

enable_testing()

add_executable(test_wavetable
    tests/test_wavetable.c
    src/wt_lerp.c
    src/wt.c
    external/unity/unity.c
)
target_include_directories(test_wavetable
    PRIVATE
    ${INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)
target_link_libraries(test_wavetable
    PRIVATE
    m
)
add_test(NAME testWavetable COMMAND test_wavetable)


add_executable(test_signal_wavetable
    tests/test_signal_wavetable.c
    src/wt_lerp.c
    src/wt.c
    external/unity/unity.c
)

target_include_directories(test_signal_wavetable
    PRIVATE
    ${INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

target_link_libraries(test_signal_wavetable
    PRIVATE
    m
)

add_test(NAME testSignalWavetable COMMAND test_signal_wavetable)


add_executable(test_sinflut
    tests/test_sinflut.c
    src/fm_lut.c
    external/unity/unity.c
)

target_include_directories(test_sinflut
    PRIVATE
    ${INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

target_link_libraries(test_sinflut
    PRIVATE
    m
)

add_test(NAME testSinfLUT COMMAND test_sinflut)
