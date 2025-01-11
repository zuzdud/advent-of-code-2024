cmake_minimum_required(VERSION 3.28)
project(advent_of_code_2024)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_subdirectory(day-01)
add_subdirectory(day-02)
add_subdirectory(day-03)
add_subdirectory(day-04)
add_subdirectory(day-05)
add_subdirectory(day-06)
add_subdirectory(day-07)
add_subdirectory(day-11)