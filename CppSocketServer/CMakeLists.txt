# 设置最低 CMake 版本
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# 设置构建目录为 build
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# 生成 Visual Studio 解决方案文件到 build 目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 项目名称和语言
project(CppSocketServer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

#include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(CppSocketServer 
    app/main.cpp 
    src/fileinit.cpp
    src/radixsort.cpp
    src/socket.cpp
    src/threadForCout.cpp
    include/fileinit.h
    include/radixsort.h
    include/socket.h
    include/threadForCout.h
)

#target_link_libraries(CppSocketServer PRIVATE ${CONAN_LIBS})
