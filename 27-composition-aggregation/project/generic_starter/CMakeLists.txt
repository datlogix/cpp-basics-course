cmake_minimum_required(VERSION 3.16)
project(SchoolStructure LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO (Part 2): once you've split model.h into one file per class,
# list every .cpp file here.
add_executable(school_structure
    src/main.cpp
    src/model.cpp
)

target_include_directories(school_structure PRIVATE include)
target_compile_options(school_structure PRIVATE -Wall -Wextra)
