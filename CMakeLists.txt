cmake_minimum_required(VERSION 3.27)
project(PulsarionMath)
set(CMAKE_CXX_STANDARD 20)

if (DEFINED PULSARION_MATH_HEADER_ONLY)
    add_library(PulsarionMath INTERFACE)
    add_compile_definitions(PULSARION_MATH_HEADER_ONLY)
    target_include_directories(PulsarionMath INTERFACE src)
    target_link_libraries(PulsarionMath INTERFACE PulsarionCore)
    target_link_libraries(PulsarionMath INTERFACE xsimd)
    return()
endif()
add_library(PulsarionMath STATIC 
        src/PulsarionMath/Core.hpp
        src/PulsarionMath/Vector.hpp
        src/PulsarionMath/MatrixTransform.hpp
        src/PulsarionMath/Matrix.hpp
        src/PulsarionMath/Math.hpp
        src/PulsarionMath/Math.cpp
        src/PulsarionMath/Quaternion.hpp
        src/PulsarionMath/Constants.hpp
        src/PulsarionMath/Conversion.hpp
)

add_subdirectory(vendor/xsimd)

target_link_libraries(PulsarionMath PUBLIC PulsarionCore)
target_link_libraries(PulsarionMath PUBLIC xsimd)

target_include_directories(PulsarionMath PUBLIC src)
