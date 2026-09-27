cmake_minimum_required(VERSION 3.15)
project(embedded_synth_lib VERSION 1.0.0 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(IMPLS
    wt_trunc
    wt_lerp
    
    fm_lut
    fm_sin
)

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
    $<INSTALL_INTERFACE:/include>
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
