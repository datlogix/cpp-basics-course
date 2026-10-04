cmake_minimum_required(VERSION 3.16)
project(VitalSigns LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(vital_signs
    src/main.cpp
    src/monitor.cpp
)

target_include_directories(vital_signs PRIVATE include)
target_compile_options(vital_signs PRIVATE -Wall -Wextra)
