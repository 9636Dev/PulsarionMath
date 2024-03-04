cmake_minimum_required(VERSION 3.27)
project(PulsarionMath VERSION 0.0.1 LANGUAGES CXX DESCRIPTION "A math library for games and graphics")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PULSARION_SIMD "SSE4.1" CACHE STRING "Choose the SIMD instruction set: SSE4.1, AVX")
set_property(CACHE PULSARION_SIMD PROPERTY STRINGS "None" "SSE4.1")

set(PULSARION_MATRIX_MAJOR "Column" CACHE STRING "Choose the major matrix order: Column, Row, or Both")
set_property(CACHE PULSARION_MATRIX_MAJOR PROPERTY STRINGS "Column" "Row" "Both")

set(PULSARION_MATH_HEADERS
    src/PulsarionMath/Core.hpp
    src/PulsarionMath/Qualifier.hpp
    src/PulsarionMath/DataStorage.hpp
    src/PulsarionMath/Vector.hpp
    src/PulsarionMath/VectorCommon.hpp
    src/PulsarionMath/Matrix.hpp
    src/PulsarionMath/MatrixCommon.hpp
)

if (PULSARION_SIMD STREQUAL "SSE4.1")
    message(STATUS "PulsarionMath: Using SSE4.1 SIMD instruction set")
    set(PULSARION_MATH_SOURCES
        src/PulsarionMath/Vector4PackedSSE.hpp
        src/PulsarionMath/Vector4AlignedSSE.hpp
        src/PulsarionMath/Matrix4x4MSSE.hpp
    )
elseif (PULSARION_SIMD STREQUAL "None" OR NOT DEFINED PULSARION_SIMD)
    message(STATUS "PulsarionMath: No SIMD instruction set selected")
    set(PULSARION_MATH_SOURCES
        src/PulsarionMath/Vector4Packed.hpp
        src/PulsarionMath/Vector4Aligned.hpp
        src/PulsarionMath/Matrix4x4M.hpp
    )
else()
    message(FATAL_ERROR "PulsarionMath: PULSARION_SIMD must be either SSE4.1, AVX, or None")
endif()

add_library(PulsarionMath INTERFACE ${PULSARION_MATH_HEADERS} ${PULSARION_MATH_SOURCES})

add_dependencies(PulsarionMath PulsarionCore)
target_link_libraries(PulsarionMath INTERFACE PulsarionCore)
target_include_directories(PulsarionMath INTERFACE src)

if (PULSARION_MATRIX_MAJOR STREQUAL "Column")
    message(STATUS "PulsarionMath: Using column major matrix order")
    target_compile_definitions(PulsarionMath INTERFACE PULSARION_MATH_MATRIX_COLUMN_MAJOR)
elseif (PULSARION_MATRIX_MAJOR STREQUAL "Row")
    message(STATUS "PulsarionMath: Using row major matrix order")
    target_compile_definitions(PulsarionMath INTERFACE PULSARION_MATH_MATRIX_ROW_MAJOR)
elseif (PULSARION_MATRIX_MAJOR STREQUAL "Both")
    message(STATUS "PulsarionMath: Using both column and row major matrix order")
    target_compile_definitions(PulsarionMath INTERFACE PULSARION_MATH_MATRIX_BOTH_MAJOR)
else()
    message(FATAL_ERROR "PulsarionMath: PULSARION_MATRIX_MAJOR must be either Column, Row, or Both")
endif()

if (PULSARION_SIMD STREQUAL "SSE4.1")
    target_compile_definitions(PulsarionMath INTERFACE PULSARION_MATH_SIMD_SSE4_1)
    # Add Compiler flags for SSE4.1
    if (MSVC)
        target_compile_options(PulsarionMath INTERFACE "/arch:AVX") # SSE4.1 is included in AVX
    else()
        target_compile_options(PulsarionMath INTERFACE "-msse4.1")
    endif()
elseif (PULSARION_SIMD STREQUAL "None" OR NOT DEFINED PULSARION_SIMD)
    target_compile_definitions(PulsarionMath INTERFACE PULSARION_MATH_SIMD_NONE)
endif()

if (NOT DEFINED PULSARION_MATH_NO_BUILD_TESTS)
    add_subdirectory(tests)
endif()
