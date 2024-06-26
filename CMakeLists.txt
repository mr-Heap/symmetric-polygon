cmake_minimum_required(VERSION 3.28)
project(symmetric_polygon)

set(CMAKE_CXX_STANDARD 17)

add_executable(symmetric_polygon main.cpp
        polygon.h
        polygon.cpp)
