cmake_minimum_required(VERSION 3.27.4 FATAL_ERROR)
project(CppSocketServer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT CppSocketServer)

# Include Conan generated files
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

if(WIN32)
    set(CMAKE_GENERATOR_PLATFORM "x64")
    set(CMAKE_GENERATOR "Visual Studio 17 2022")
endif()

file(GLOB_RECURSE 
    head 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(all_files ${head} ${src})   

#find_package(Boost REQUIRED)
find_package(Boost 1.83.0 REQUIRED COMPONENTS thread system random chrono)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})


# CppSocketServer
add_executable(CppSocketServer 
    app/main.cpp 
    ${all_files}
)
target_include_directories(CppSocketServer 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_INCLUDE_PATH}
)
set_target_properties(CppSocketServer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin_server
)
target_link_libraries(CppSocketServer
${Boost_LIBRARIES}
)
configure_file(cfg/listen_cmd_server_cfg.json ${CMAKE_BINARY_DIR}/listen_cmd_server_cfg.json COPYONLY)


#######################################WebSocketServer######################################
add_executable(CppWebSocketServer
    app/WebSocketMain.cpp 
    ${all_files}
)

target_include_directories(CppWebSocketServer 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_INCLUDE_PATH}
    )
target_link_libraries(CppWebSocketServer 
${Boost_LIBRARIES}
)
set_target_properties(CppWebSocketServer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/websocket
)
configure_file(cfg/config.txt ${CMAKE_BINARY_DIR}/config.txt COPYONLY)
#######################################another one######################################
file(GLOB_RECURSE src2 ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)
set(all_files_2 ${head} ${src} ${src2})

foreach(file ${all_files_2})
    file(RELATIVE_PATH relative_file ${CMAKE_CURRENT_SOURCE_DIR} ${file})
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" relative_group ${relative_file})
    string(REPLACE "/" "\\" relative_group ${relative_group})
    source_group(${relative_group} FILES ${file})
endforeach()

add_executable(Test1Any
    ${all_files_2}
)

target_include_directories(Test1Any 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_INCLUDE_PATH}
    )
set_target_properties(Test1Any PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin_test
)
configure_file(cfg/cout.bat ${CMAKE_BINARY_DIR}/bin_test/Debug/cout.bat COPYONLY)


#######################################another one######################################

file(GLOB_RECURSE src3 ${CMAKE_CURRENT_SOURCE_DIR}/test2/*.cpp)
set(all_files_3 ${head} ${src} ${src3})

foreach(file ${all_files_3})
    file(RELATIVE_PATH relative_file ${CMAKE_CURRENT_SOURCE_DIR} ${file})
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" relative_group ${relative_file})
    string(REPLACE "/" "\\" relative_group ${relative_group})
    source_group(${relative_group} FILES ${file})
endforeach()

add_executable(Test2Any
    ${all_files_3}
)

target_include_directories(Test2Any 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_INCLUDE_PATH}
    )
set_target_properties(Test2Any PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin_test2
)