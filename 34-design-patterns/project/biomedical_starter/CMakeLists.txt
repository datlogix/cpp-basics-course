cmake_minimum_required(VERSION 3.16)
project(PatternsProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO: add a .cpp file for each class you create.
add_executable(ward_platform
    src/main.cpp
)

target_include_directories(ward_platform PRIVATE include)
target_compile_options(ward_platform PRIVATE -Wall -Wextra)
