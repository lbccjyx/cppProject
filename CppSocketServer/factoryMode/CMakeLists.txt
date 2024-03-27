file(GLOB_RECURSE head ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
set(all_files ${head} ${src})

# 创建一个库
add_library(FactoryMode ${all_files})
