cmake_minimum_required(VERSION 3.16)
project(SchoolClubs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(school_clubs
    src/main.cpp
    src/student.cpp
    # TODO: add src/club.cpp here once you've created it
)

target_include_directories(school_clubs PRIVATE include)
target_compile_options(school_clubs PRIVATE -Wall -Wextra)
