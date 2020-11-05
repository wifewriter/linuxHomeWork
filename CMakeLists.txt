cmake_minimum_required(VERSION 3.15)
project(linux_for_yy2020)

MESSAGE("project linux_for_yy2020")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE DEBUG)

include_directories(./include)

add_subdirectory(include)
add_subdirectory(src)

add_executable(linux_for_yy2020 src/main.cpp)