cmake_minimum_required(VERSION 3.16)
project(ValueType LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(impedance
    src/main.cpp
    src/impedance.cpp
)

target_include_directories(impedance PRIVATE include)
target_compile_options(impedance PRIVATE -Wall -Wextra)
