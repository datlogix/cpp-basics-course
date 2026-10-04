cmake_minimum_required(VERSION 3.16)
project(SchoolOwnership LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(school_ownership
    src/main.cpp
    src/staff.cpp
    src/school.cpp
    src/club.cpp
)

target_include_directories(school_ownership PRIVATE include)
target_compile_options(school_ownership PRIVATE -Wall -Wextra)
