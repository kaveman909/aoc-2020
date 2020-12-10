cmake_minimum_required(VERSION 3.19)

project(AOC_2020)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

enable_testing()

# Library Section
add_library(aocutil STATIC src/aoc_util.cpp)

foreach(x RANGE 1 5)

# AoC Days Section

add_executable(day${x} src/${x}.cpp)
target_link_libraries(day${x} PUBLIC fmt aocutil)

# Test Section

add_test(NAME d${x} COMMAND day${x} $ENV{HOME}/aoc-2020/input/${x}.txt)
add_test(NAME d${x}a COMMAND day${x} $ENV{HOME}/aoc-2020/input/${x}a.txt)

endforeach()
