cmake_minimum_required(VERSION 3.2.2)

project(yokoi CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=clock++11")

include_directories(include)

include_directories(/usr/local/Cellar/sdl2/2.0.3/include)

link_libraries(/usr/local/Cellar/sdl2/2.0.3/lib)

add_executable(yokoi src/main.cpp include/Time.h)
