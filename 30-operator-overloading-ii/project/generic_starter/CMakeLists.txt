cmake_minimum_required(VERSION 3.16)
project(ValueType LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(school_fees
    src/main.cpp
    src/money.cpp
)

target_include_directories(school_fees PRIVATE include)
target_compile_options(school_fees PRIVATE -Wall -Wextra)
