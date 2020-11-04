cmake_minimum_required(VERSION 3.15)
project(linux_for_yy2020)

set(CMAKE_CXX_STANDARD 14)

add_executable(linux_for_yy2020 main.cpp src/FileHander.cpp include/FileHander.h include/GloableDefine.cpp include/GloableDefine.h)