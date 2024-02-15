cmake_minimum_required(VERSION 3.27)
project(PulsarionMath VERSION 0.0.1 LANGUAGES CXX DESCRIPTION "A math library for games and graphics")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PULSARION_SIMD "SSE4.1" CACHE STRING "Choose the SIMD instruction set: SSE4.1, AVX")
set_property(CACHE PULSARION_SIMD PROPERTY STRINGS "SSE4.1" "AVX")

set(PULSARION_MATRIX_MAJOR "Column" CACHE STRING "Choose the major matrix order: Column, Row, or Both")
set_property(CACHE PULSARION_MATRIX_MAJOR PROPERTY STRINGS "Column" "Row" "Both")

if (DEFINED PULSARION_MATH_STANDALONE)
    MESSAGE(STATUS "PulsarionMath: Building standalone")

    # Get PulsarionCore using FetchContent
    include(FetchContent)
    message(FATAL_ERROR "PulsarionMath: Standalone build is not supported yet!")
endif()

# There is issue with MSVC and C++20, where it uses the default C++14 standard when building INTERFACE libraries

if (NOT DEFINED PULSARION_LIBRARY_TYPE)
    message(FATAL_ERROR "PulsarionMath: PULSARION_LIBRARY_TYPE is not defined, include PulsarionCore first!")
endif()

if (DEFINED PULSARION_MATH_HEADER_ONLY)
    MESSAGE(STATUS "PulsarionMath: Using header only mode")
    add_library(PulsarionMath INTERFACE
            src/PulsarionMath/Core.hpp
            src/PulsarionMath/Vector.hpp
            src/PulsarionMath/MatrixTransform.hpp
            src/PulsarionMath/Matrix.hpp
            src/PulsarionMath/Math.hpp
            src/PulsarionMath/Quaternion.hpp
            src/PulsarionMath/Constants.hpp
            src/PulsarionMath/Conversion.hpp
            src/PulsarionMath/EulerAngle.hpp
            src/PulsarionMath/Complex.hpp
    )

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
        message(STATUS "PulsarionMath: Using SSE4.1 SIMD instruction set")
        target_compile_definitions(PulsarionMath INTERFACE PULSARION_MATH_SIMD_SSE4_1)
        # Add Compiler flags for SSE4.1
        if (MSVC)
            target_compile_options(PulsarionMath INTERFACE "/arch:AVX") # SSE4.1 is included in AVX
        else()
            target_compile_options(PulsarionMath INTERFACE "-msse4.1")
        endif()
    elseif (PULSARION_SIMD STREQUAL "AVX")
        message(STATUS "PulsarionMath: Using AVX SIMD instruction set")
        target_compile_definitions(PulsarionMath INTERFACE PULSARION_MATH_SIMD_AVX)
        if (MSVC)
            target_compile_options(PulsarionMath INTERFACE "/arch:AVX")
        else()
            target_compile_options(PulsarionMath INTERFACE"-mavx")
        endif()
    elseif (PULSARION_SIMD STREQUAL "None" OR NOT DEFINED PULSARION_SIMD)
        message(STATUS "PulsarionMath: No SIMD instruction set selected")
        target_compile_definitions(PulsarionMath INTERFACE PULSARION_MATH_SIMD_NONE)
    else()
        message(FATAL_ERROR "PulsarionMath: PULSARION_SIMD must be either SSE4.1, AVX, or None")
    endif()
else()
    # Only ever build as static library, since there are no exports, and only one arbituary source file
    add_library(PulsarionMath STATIC
            src/PulsarionMath/Core.hpp
            src/PulsarionMath/Simd.hpp
            src/PulsarionMath/Vector.hpp
            src/PulsarionMath/MatrixTransform.hpp
            src/PulsarionMath/Matrix.hpp
            src/PulsarionMath/Math.hpp
            src/PulsarionMath/Math.cpp
            src/PulsarionMath/Quaternion.hpp
            src/PulsarionMath/Constants.hpp
            src/PulsarionMath/Conversion.hpp
            src/PulsarionMath/Matrix/Util.hpp
    )


    add_dependencies(PulsarionMath PulsarionCore)
    target_link_libraries(PulsarionMath PUBLIC PulsarionCore)

    target_include_directories(PulsarionMath PUBLIC src)

    if (PULSARION_MATRIX_MAJOR STREQUAL "Column")
        message(STATUS "PulsarionMath: Using column major matrix order")
        target_compile_definitions(PulsarionMath PUBLIC PULSARION_MATH_MATRIX_COLUMN_MAJOR)
    elseif (PULSARION_MATRIX_MAJOR STREQUAL "Row")
        message(STATUS "PulsarionMath: Using row major matrix order")
        target_compile_definitions(PulsarionMath PUBLIC PULSARION_MATH_MATRIX_ROW_MAJOR)
    elseif (PULSARION_MATRIX_MAJOR STREQUAL "Both")
        message(STATUS "PulsarionMath: Using both column and row major matrix order")
        target_compile_definitions(PulsarionMath PUBLIC PULSARION_MATH_MATRIX_BOTH_MAJOR)
    else()
        message(FATAL_ERROR "PulsarionMath: PULSARION_MATRIX_MAJOR must be either Column, Row, or Both")
    endif()

    if (PULSARION_SIMD STREQUAL "SSE4.1")
        message(STATUS "PulsarionMath: Using SSE4.1 SIMD instruction set")
        target_compile_definitions(PulsarionMath PUBLIC PULSARION_MATH_SIMD_SSE4_1)
        # Add Compiler flags for SSE4.1
        if (MSVC)
            target_compile_options(PulsarionMath PUBLIC "/arch:AVX") # SSE4.1 is included in AVX
        else()
            target_compile_options(PulsarionMath PUBLIC "-msse4.1")
        endif()
    elseif (PULSARION_SIMD STREQUAL "AVX")
        message(STATUS "PulsarionMath: Using AVX SIMD instruction set")
        target_compile_definitions(PulsarionMath PUBLIC PULSARION_MATH_SIMD_AVX)
        if (MSVC)
            target_compile_options(PulsarionMath PUBLIC "/arch:AVX")
        else()
            target_compile_options(PulsarionMath PUBLIC "-mavx")
        endif()
    elseif (PULSARION_SIMD STREQUAL "None" OR NOT DEFINED PULSARION_SIMD)
        message(STATUS "PulsarionMath: No SIMD instruction set selected")
        target_compile_definitions(PulsarionMath PUBLIC PULSARION_MATH_SIMD_NONE)
    else()
        message(FATAL_ERROR "PulsarionMath: PULSARION_SIMD must be either SSE4.1, AVX, or None")
    endif()
endif()


if (NOT DEFINED PULSARION_MATH_NO_BUILD_TESTS)
    add_subdirectory(tests)
endif()
