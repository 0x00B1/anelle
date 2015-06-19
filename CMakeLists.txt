cmake_minimum_required(VERSION 3.2.2)

project(yokoi CXX)

include_directories(include)

add_executable(yokoi src/main.cpp src/MMU.h src/MMU.cpp)

set_property(TARGET yokoi PROPERTY CXX_STANDARD 11)
set_property(TARGET yokoi PROPERTY CXX_STANDARD_REQUIRED ON)
