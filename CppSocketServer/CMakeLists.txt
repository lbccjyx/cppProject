# 设置最低 CMake 版本
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)


# 项目名称和语言
project(CppSocketServer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Include Conan
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)


# 设置VS中的启动项目
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT CppSocketServer)
find_package(Boost REQUIRED)
#find_package(nlohmann_json)  由于nlohmann_json本身没有库
add_executable(CppSocketServer 
    app/main.cpp 
    src/fileinit.cpp
    src/radixsort.cpp
    src/socket.cpp
    src/threadForCout.cpp
)

target_link_libraries(CppSocketServer) #${CMAKE_LIBRARY_PATH}
target_include_directories(CppSocketServer PRIVATE ${CMAKE_INCLUDE_PATH})
set_target_properties(CppSocketServer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin_server
)
# 把cfg文件复制到相关位置 代码中就无需绝对路径或者相对路径
configure_file(cfg/listen_cmd_server_cfg.json ${CMAKE_BINARY_DIR}/listen_cmd_server_cfg.json COPYONLY)

#######################################another one######################################
add_executable(Test2Any
    test/main.cpp
    test/unit_test.cpp
    test/unit_test2.cpp
    src/threadForCout.cpp
    src/radixsort.cpp
)

target_link_libraries(Test2Any) # PRIVATE ${CMAKE_LIBRARY_PATH}
target_include_directories(Test2Any PRIVATE ${CMAKE_INCLUDE_PATH})
set_target_properties(Test2Any PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin_test
)
configure_file(cfg/cout.bat ${CMAKE_BINARY_DIR}/bin_test/Debug/cout.bat COPYONLY)
