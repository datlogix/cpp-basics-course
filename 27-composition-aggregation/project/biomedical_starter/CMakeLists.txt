cmake_minimum_required(VERSION 3.16)
project(HospitalStructure LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO (Part 2): once you've split model.h into one file per class,
# list every .cpp file here.
add_executable(hospital
    src/main.cpp
    src/model.cpp
)

target_include_directories(hospital PRIVATE include)
target_compile_options(hospital PRIVATE -Wall -Wextra)
