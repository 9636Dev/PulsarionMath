cmake_minimum_required(VERSION 3.27)
project(PulsarionMath)
set(CMAKE_CXX_STANDARD 20)

add_library(PulsarionMath INTERFACE
        src/PulsarionMath/Core.hpp
        src/PulsarionMath/Vector.hpp
        src/PulsarionMath/Matrix.hpp
        src/PulsarionMath/Math.hpp
)

add_subdirectory(vendor/xsimd)

target_link_libraries(PulsarionMath INTERFACE PulsarionCore)
target_link_libraries(PulsarionMath INTERFACE xsimd)

target_include_directories(PulsarionMath INTERFACE src)