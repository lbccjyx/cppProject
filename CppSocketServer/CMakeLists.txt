# 设置最低 CMake 版本
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)


# 项目名称和语言
project(CppSocketServer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT CppSocketServer)

add_executable(CppSocketServer 
    app/main.cpp 
    src/fileinit.cpp
    src/radixsort.cpp
    src/socket.cpp
    src/threadForCout.cpp
)
target_link_libraries(CppSocketServer PRIVATE ${CONAN_LIBS})
target_include_directories(CppSocketServer PRIVATE ${Boost_INCLUDE_DIRS})  # Add this line to include Boost headers

#######################################another one######################################
find_package(Boost REQUIRED)
add_executable(Test2Any
    test/main.cpp
    test/test_calculator.cpp
)

target_link_libraries(Test2Any PRIVATE ${CONAN_LIBS}) # Boost::boost
target_include_directories(Test2Any PRIVATE ${Boost_INCLUDE_DIRS})  # Add this line to include Boost headers

set_target_properties(Test2Any PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
