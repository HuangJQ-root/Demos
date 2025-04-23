cmake_minimum_required(VERSION 3.12)

set(Project_Name Gtest_Demo)

project(${Project_Name})

enable_language(C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

set(Headers
    include/example.h
)

set(Sources
    src/example.c
)

add_library(${Project_Name} STATIC ${Sources} ${Headers})

# 设置头文件搜索路径
target_include_directories(${Project_Name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)