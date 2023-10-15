cmake_minimum_required(VERSION 3.10)
project(chino_acm_template)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe -std=c99 -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++11 -O2")

add_subdirectory(example)

add_subdirectory(template)

add_subdirectory(playground)