cmake_minimum_required(VERSION 3.22)
project(EngProj)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(EngProj apsc143project.cpp colours.cpp colours.h)
