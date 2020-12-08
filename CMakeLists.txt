cmake_minimum_required(VERSION 3.19)

project(AOC_2020)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Release)

include_directories(include)

# Library Section
add_library(aocutil STATIC src/aoc_util.cpp)

# AoC Days Section
add_executable(day1 src/1.cpp)
target_link_libraries(day1 PUBLIC fmt)

add_executable(day2 src/2.cpp)
target_link_libraries(day2 PUBLIC fmt aocutil)

# Test Section
enable_testing()
add_test(NAME d1 COMMAND day1 ../input/1.txt)
add_test(NAME d2 COMMAND day2 ../input/2.txt)
