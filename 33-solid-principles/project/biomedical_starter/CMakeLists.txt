cmake_minimum_required(VERSION 3.16)
project(WardRefactor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO: list your new .cpp files here as you extract classes.
add_executable(ward_refactor
    src/main.cpp
    src/ward_manager.cpp
)

target_include_directories(ward_refactor PRIVATE include)
target_compile_options(ward_refactor PRIVATE -Wall -Wextra)
