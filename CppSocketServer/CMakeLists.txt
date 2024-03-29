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

file(GLOB_RECURSE head ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE head2 ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(all_files ${head} ${head2} ${src})

add_executable(CppSocketServer 
    app/main.cpp 
    ${all_files}
)

target_link_libraries(CppSocketServer) #${CMAKE_LIBRARY_PATH}
target_include_directories(CppSocketServer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(CppSocketServer PRIVATE ${CMAKE_INCLUDE_PATH})
set_target_properties(CppSocketServer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin_server
)

# 把cfg文件复制到相关位置 代码中就无需绝对路径或者相对路径
configure_file(cfg/listen_cmd_server_cfg.json ${CMAKE_BINARY_DIR}/listen_cmd_server_cfg.json COPYONLY)

#######################################another one######################################

file(GLOB_RECURSE head ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE head2 ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(all_files ${head} ${head2} ${src})

foreach(file ${all_files})
    file(RELATIVE_PATH relative_file ${CMAKE_CURRENT_SOURCE_DIR} ${file})
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" relative_group ${relative_file})
    string(REPLACE "/" "\\" relative_group ${relative_group})
    source_group(${relative_group} FILES ${file})
endforeach()

add_executable(Test2Any
    ${all_files}
)

target_include_directories(Test2Any PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(Test2Any PRIVATE ${CMAKE_INCLUDE_PATH})
set_target_properties(Test2Any PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin_test
)
configure_file(cfg/cout.bat ${CMAKE_BINARY_DIR}/bin_test/Debug/cout.bat COPYONLY)
