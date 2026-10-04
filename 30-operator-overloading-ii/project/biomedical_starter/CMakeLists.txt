cmake_minimum_required(VERSION 3.16)
project(ValueType LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(doses
    src/main.cpp
    src/dose.cpp
)

target_include_directories(doses PRIVATE include)
target_compile_options(doses PRIVATE -Wall -Wextra)
