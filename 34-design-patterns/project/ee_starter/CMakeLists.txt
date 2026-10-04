cmake_minimum_required(VERSION 3.16)
project(PatternsProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO: add a .cpp file for each class you create.
add_executable(smart_home
    src/main.cpp
)

target_include_directories(smart_home PRIVATE include)
target_compile_options(smart_home PRIVATE -Wall -Wextra)
