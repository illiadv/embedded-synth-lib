cmake_minimum_required(VERSION 3.15)
project(embedded_synth_lib VERSION 1.0.0 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(IMPLS
    "wt_trunc"
    "wt_lerp"
    
    "fm_lut"
    "fm_sin"
)

set(ACTIVE_IMPL "wt_truc" CACHE STRING "Selected implementation to build")
set_property(CACHE ACTIVE_IMPL PROPERTY STRINGS ${ALL_IMPLS})

string(SUBSTRING ${ACTIVE_IMPL} 0 2 SYNTH_METHOD)

message("Building implementation ${ACTIVE_IMPL}")
message("Synthesis method is ${SYNTH_METHOD}")

if ("${SYNTH_METHOD}" STREQUAL "wt")
    set(TARGET_INIT_DEF "InitOsc_${SYNTH_METHOD}(&_wt_osc_default freq 0 1.0f")
elseif("${SYNTH_METHOD}" STREQUAL "fm")
    set(TARGET_INIT_DEF "InitOsc_${SYNTH_METHOD}(&_fm_osc_default freq 1.0f 0 1.0f")
else()
    message(FATAL_ERROR "Wrong synth method selected")
endif()

set(TARGET_IMPL_DEF "GetSample_${ACTIVE_IMPL}")

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/synth_lib/api.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/generated/api.h
  @ONLY
)

# Target #1 - all implementations (for desktop)

set(ALL_SOURCES
    src/wt.c
    src/fm.c
)

foreach(impl IN LISTS IMPLS)
    list(APPEND ALL_SOURCES src/${impl}.c)
endforeach()

add_library(synth
    ${ALL_SOURCES}
)

target_include_directories(synth
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Target #2 - specific implementation (for stm32)

add_library(synth_stm32
    src/${SYNTH_METHOD}.c
    src/${ACTIVE_IMPL}.c
)

target_include_directories(synth_stm32
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated/>

)


# Tests

enable_testing()

add_executable(test_wt_lerp
    tests/test_wt_lerp.c
    src/wt_lerp.c
    src/wt.c
    external/unity/unity.c
)
target_include_directories(test_wt_lerp
    PRIVATE
    ${INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)
target_link_libraries(test_wt_lerp
    PRIVATE
    m
)
add_test(NAME testWavetable COMMAND test_wt_lerp)


add_executable(test_wt_signal
    tests/test_wt_signal.c
    src/wt_lerp.c
    src/wt.c
    external/unity/unity.c
)

target_include_directories(test_wt_signal
    PRIVATE
    ${INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

target_link_libraries(test_wt_signal
    PRIVATE
    m
)

add_test(NAME testSignalWavetable COMMAND test_wt_signal)


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
