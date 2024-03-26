# 将所有的源文件添加到一个变量中
set(FACTORY_MODE_SRC
    Product.cpp
    Factory.cpp
)

# 创建一个库
add_library(FactoryMode ${FACTORY_MODE_SRC})

# 设置头文件的搜索路径
# target_include_directories(FactoryMode PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
