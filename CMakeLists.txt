cmake_minimum_required(VERSION 3.28)
project(symmetric_polygon)

set(CMAKE_CXX_STANDARD 17)


enable_testing()

add_subdirectory(googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(symmetric_polygon main.cpp
        polygon.h
        polygon.cpp
        tests/tests.cpp)


target_link_libraries(symmetric_polygon GTest::gtest GTest::gtest_main)

add_test(NAME tests COMMAND symmetric-polygon)