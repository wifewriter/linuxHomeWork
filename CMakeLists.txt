cmake_minimum_required(VERSION 3.15)
project(linux_for_yy2020)

MESSAGE("project linux_for_yy2020")
set(CMAKE_CXX_STANDARD 14)
#当前是DEBUG模式
set(CMAKE_BUILD_TYPE DEBUG)
#引入所有需编译的源文件
aux_source_directory(./include DIR_INCLUDE)
aux_source_directory(./src DIR_SRC)
#头文件文件夹
include_directories(./include)

#设置编译器使用c++11
#add_definitions(-std=c++11)

#设置执行文件输出到指定位置
#set(EXECUTABLE_OUTPUT_PATH ./install)
#设置库文件输出位置
#set(LIBRARY_OUTPUT_PATH  ./lib)

#add_subdirectory(include)
#add_subdirectory(src)

add_executable(linux_for_yy2020 main.cpp ${DIR_INCLUDE} ${DIR_SRC})
