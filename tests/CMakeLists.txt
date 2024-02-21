cmake_minimum_required(VERSION 3.27)
project(PulsarionMathTests)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PULSARION_MATH_TEST_SOURCES
    Vector4PackedTests.cpp
)
add_executable(PulsarionMathTests ${PULSARION_MATH_TEST_SOURCES})

add_dependencies(PulsarionMathTests PulsarionCore)
add_dependencies(PulsarionMathTests PulsarionMath)
target_link_libraries(PulsarionMathTests PRIVATE PulsarionCore)
target_link_libraries(PulsarionMathTests PRIVATE PulsarionMath)

if (NOT TARGET gtest_main)
    add_subdirectory(vendor/googletest)
endif()

enable_testing()
include(GoogleTest)

target_link_libraries(PulsarionMathTests PRIVATE gtest_main)

gtest_discover_tests(PulsarionMathTests)
