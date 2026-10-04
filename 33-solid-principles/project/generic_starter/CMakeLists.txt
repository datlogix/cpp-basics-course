cmake_minimum_required(VERSION 3.16)
project(SchoolRefactor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO: list your new .cpp files here as you extract classes.
add_executable(school_refactor
    src/main.cpp
    src/school_manager.cpp
)

target_include_directories(school_refactor PRIVATE include)
target_compile_options(school_refactor PRIVATE -Wall -Wextra)
