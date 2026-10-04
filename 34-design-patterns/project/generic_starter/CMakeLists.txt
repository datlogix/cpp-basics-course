cmake_minimum_required(VERSION 3.16)
project(PatternsProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO: add a .cpp file for each class you create.
add_executable(school_events
    src/main.cpp
)

target_include_directories(school_events PRIVATE include)
target_compile_options(school_events PRIVATE -Wall -Wextra)
