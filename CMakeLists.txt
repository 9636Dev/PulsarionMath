cmake_minimum_required(VERSION 3.27)
project(PulsarionMath VERSION 0.0.1 LANGUAGES CXX DESCRIPTION "A math library for games and graphics")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PULSARION_SIMD "SSE4.1" CACHE STRING "Choose the SIMD instruction set: SSE4.1, AVX")
set_property(CACHE PULSARION_SIMD PROPERTY STRINGS "None" "SSE4.1")

set(PULSARION_MATRIX_MAJOR "Column" CACHE STRING "Choose the major matrix order: Column, Row, or Both")
set_property(CACHE PULSARION_MATRIX_MAJOR PROPERTY STRINGS "Column" "Row" "Both")

if (NOT DEFINED PULSARION_LIBRARY_TYPE)
    message(FATAL_ERROR "PulsarionMath: PULSARION_LIBRARY_TYPE is not defined, include PulsarionCore first!")
endif()

set(PULSARION_MATH_HEADERS
    src/PulsarionMath/Core.hpp
    src/PulsarionMath/Qualifier.hpp
    src/PulsarionMath/DataStorage.hpp
    src/PulsarionMath/Vector.hpp
)

# The inline files that should compile with the library
set(PULSARION_MATH_SOURCES
    src/PulsarionMath/Vector.inl
)

if (PULSARION_MATH_HEADER_ONLY STREQUAL "ON" OR PULSARION_MATH_HEADER_ONLY STREQUAL "TRUE" OR PULSARION_MATH_HEADER_ONLY STREQUAL "1")
    MESSAGE(STATUS "PulsarionMath: Using header only mode")
    add_library(PulsarionMath INTERFACE ${PULSARION_MATH_HEADERS} ${PULSARION_MATH_SOURCES})
    target_compile_definitions(PulsarionMath INTERFACE PULSARION_MATH_HEADER_ONLY)
    set(PULSARION_MATH_TYPE INTERFACE)
else()
    MESSAGE(FATAL_ERROR "PulsarionMath: Not implemented yet")
    # Only ever build as static library, since there are no exports, and only one arbitrary source file
    # add_library(PulsarionMath STATIC
    #    ${PULSARION_MATH_HEADERS}
    #    ${PULSARION_MATH_SOURCES}
    #)

    # if (PULSARION_LIBRARY_TYPE STREQUAL "SHARED")
    #     target_compile_definitions(PulsarionMath PRIVATE PULSARION_BUILD_DLL)
    # endif()

    set(PULSARION_MATH_TYPE PUBLIC)
endif()

add_dependencies(PulsarionMath PulsarionCore)
target_link_libraries(PulsarionMath ${PULSARION_MATH_TYPE} PulsarionCore)

target_include_directories(PulsarionMath ${PULSARION_MATH_TYPE} src)

if (PULSARION_MATRIX_MAJOR STREQUAL "Column")
    message(STATUS "PulsarionMath: Using column major matrix order")
    target_compile_definitions(PulsarionMath ${PULSARION_MATH_TYPE} PULSARION_MATH_MATRIX_COLUMN_MAJOR)
elseif (PULSARION_MATRIX_MAJOR STREQUAL "Row")
    message(STATUS "PulsarionMath: Using row major matrix order")
    target_compile_definitions(PulsarionMath ${PULSARION_MATH_TYPE} PULSARION_MATH_MATRIX_ROW_MAJOR)
elseif (PULSARION_MATRIX_MAJOR STREQUAL "Both")
    message(STATUS "PulsarionMath: Using both column and row major matrix order")
    target_compile_definitions(PulsarionMath ${PULSARION_MATH_TYPE} PULSARION_MATH_MATRIX_BOTH_MAJOR)
else()
    message(FATAL_ERROR "PulsarionMath: PULSARION_MATRIX_MAJOR must be either Column, Row, or Both")
endif()

if (PULSARION_SIMD STREQUAL "SSE4.1")
    message(STATUS "PulsarionMath: Using SSE4.1 SIMD instruction set")
    target_compile_definitions(PulsarionMath ${PULSARION_MATH_TYPE} PULSARION_MATH_SIMD_SSE4_1)
    # Add Compiler flags for SSE4.1
    if (MSVC)
        target_compile_options(PulsarionMath ${PULSARION_MATH_TYPE} "/arch:AVX") # SSE4.1 is included in AVX
    else()
        target_compile_options(PulsarionMath ${PULSARION_MATH_TYPE} "-msse4.1")
    endif()
elseif (PULSARION_SIMD STREQUAL "None" OR NOT DEFINED PULSARION_SIMD)
    message(STATUS "PulsarionMath: No SIMD instruction set selected")
    target_compile_definitions(PulsarionMath ${PULSARION_MATH_TYPE} PULSARION_MATH_SIMD_NONE)
else()
    message(FATAL_ERROR "PulsarionMath: PULSARION_SIMD must be either SSE4.1, AVX, or None")
endif()

if (NOT DEFINED PULSARION_MATH_NO_BUILD_TESTS)
    add_subdirectory(tests)
endif()
