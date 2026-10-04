cmake_minimum_required(VERSION 3.16)
project(TeachingResearchers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(teaching_researchers
    src/main.cpp
    src/people.cpp
)

target_include_directories(teaching_researchers PRIVATE include)
target_compile_options(teaching_researchers PRIVATE -Wall -Wextra)
