# 设置最低 CMake 版本
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)


# 项目名称和语言
project(CppSocketServer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(CppSocketServer 
    app/main.cpp 
    src/fileinit.cpp
    src/radixsort.cpp
    src/socket.cpp
    src/threadForCout.cpp
)

target_link_libraries(CppSocketServer PRIVATE ${CONAN_LIBS})
