cmake_minimum_required(VERSION 3.15)
project(embedded_synth_lib VERSION 1.0.0 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(IMPLS
    "wt_trunc"
    "wt_lerp"
    
    "fm_lut"
    "fm_sin"
    "fm_lut_lerp"
)

set(ACTIVE_IMPL "wt_trunc" CACHE STRING "Selected implementation to build")
set_property(CACHE ACTIVE_IMPL PROPERTY STRINGS ${ALL_IMPLS})

string(SUBSTRING ${ACTIVE_IMPL} 0 2 SYNTH_METHOD)

message("Building implementation ${ACTIVE_IMPL}")
message("Synthesis method is ${SYNTH_METHOD}")

if ("${SYNTH_METHOD}" STREQUAL "wt")
    set (TARGET_OSC_DEF "WT_Oscillator")
    set(TARGET_INIT_DEF "InitOsc_${SYNTH_METHOD}(&osc, freq, 0, 1.0f)")
elseif("${SYNTH_METHOD}" STREQUAL "fm")
    set (TARGET_OSC_DEF "FM_Oscillator")
    set(TARGET_INIT_DEF "InitOsc_${SYNTH_METHOD}(&osc, freq, 1.0f, 0, 1.0f)")
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
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated/>
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

# Header generation

find_package(Python3 COMPONENTS Interpreter REQUIRED)

# 1. Wavetable generation

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/generated/wavetables.h"
    COMMAND Python3::Interpreter "${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_wavetables.py"
            --output-path "${CMAKE_CURRENT_BINARY_DIR}/generated/wavetables.h"
	    --table-length 512
	    --max-sample-value 32767
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_wavetables.py"
    COMMENT "Generating wave tables..."
    VERBATIM
)

set_source_files_properties(src/wt.c
    PROPERTIES OBJECT_DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/generated/wavetables.h"
)

# 2. Sine LUT generation

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/generated/sin_lut.h"
    COMMAND Python3::Interpreter "${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_sin_lut.py"
            --output-path "${CMAKE_CURRENT_BINARY_DIR}/generated/sin_lut.h"
	    --table-length 256
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_sin_lut.py"
    COMMENT "Generating sine LUT..."
    VERBATIM
)

set_source_files_properties(src/fm_lut.c
    PROPERTIES OBJECT_DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/generated/sin_lut.h"
)


# Tests

enable_testing()

add_executable(test_api
    tests/test_api.c
    src/${SYNTH_METHOD}.c
    src/${ACTIVE_IMPL}.c
    external/unity/unity.c
)

target_include_directories(test_api
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/generated
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

target_link_libraries(test_api
    PRIVATE
    m
)

add_test(NAME testApi COMMAND test_api)

add_custom_target(stm32 DEPENDS synth_stm32 test_api)
