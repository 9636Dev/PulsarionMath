cmake_minimum_required(VERSION 3.27)
project(PulsarionMathTests)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PULSARION_MATH_TEST_SOURCES
    QualifierTests.cpp
)
add_executable(PulsarionMathTests ${PULSARION_MATH_TEST_SOURCES})

target_link_libraries(PulsarionMathTests PRIVATE PulsarionCore)
target_link_libraries(PulsarionMathTests PRIVATE PulsarionMath)

if (NOT TARGET gtest_main)
    add_subdirectory(vendor/googletest)
endif()

enable_testing()
include(GoogleTest)

target_link_libraries(PulsarionMathTests PRIVATE gtest_main)

gtest_discover_tests(PulsarionMathTests)
