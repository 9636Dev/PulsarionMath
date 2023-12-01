cmake_minimum_required(VERSION 3.27)
project(PulsarionMath)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendor/xsimd)

# There is issue with MSVC and C++20, where it uses the default C++14 standard when building INTERFACE libraries

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
    )

    target_link_libraries(PulsarionMath INTERFACE PulsarionCore)
    target_link_libraries(PulsarionMath INTERFACE xsimd)

    target_include_directories(PulsarionMath INTERFACE src)
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

target_link_libraries(PulsarionMath PUBLIC PulsarionCore)
target_link_libraries(PulsarionMath PUBLIC xsimd)

target_include_directories(PulsarionMath PUBLIC src)
