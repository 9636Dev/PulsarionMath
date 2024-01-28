cmake_minimum_required(VERSION 3.27)
project(PulsarionMathTests)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PULSARION_MATH_TEST_SOURCES
    MatrixNoSimdTests.cpp
    MatrixTests.cpp
    VectorNoSimdTests.cpp
    VectorTests.cpp
    MatrixTests.cpp
    MatrixTransformTests.cpp
    QuaternionTests.cpp
)
add_executable(PulsarionMathTests ${PULSARION_MATH_TEST_SOURCES})

target_link_libraries(PulsarionMathTests PRIVATE PulsarionCore)
target_link_libraries(PulsarionMathTests PRIVATE PulsarionMath)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

target_link_libraries(PulsarionMathTests PRIVATE gtest_main)

gtest_discover_tests(PulsarionMathTests)
