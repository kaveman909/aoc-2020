cmake_minimum_required(VERSION 3.19)

project(AOC_2020)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lib/fmt)

add_executable(day1 src/1.cpp)
target_link_libraries(day1 PUBLIC fmt)
target_include_directories(day1 PUBLIC "${PROJECT_SOURCE_DIR}/lib/fmt")
