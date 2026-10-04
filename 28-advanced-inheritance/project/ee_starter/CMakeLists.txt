cmake_minimum_required(VERSION 3.16)
project(SmartDevices LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(smart_devices
    src/main.cpp
    src/devices.cpp
)

target_include_directories(smart_devices PRIVATE include)
target_compile_options(smart_devices PRIVATE -Wall -Wextra)
