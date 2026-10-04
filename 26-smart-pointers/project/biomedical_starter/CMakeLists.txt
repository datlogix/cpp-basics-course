cmake_minimum_required(VERSION 3.16)
project(WardOwnership LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ward_ownership
    src/main.cpp
    src/medical_device.cpp
    src/ward.cpp
)

target_include_directories(ward_ownership PRIVATE include)
target_compile_options(ward_ownership PRIVATE -Wall -Wextra)
