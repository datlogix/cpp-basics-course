cmake_minimum_required(VERSION 3.16)
project(SensorFramework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sensor_framework
    src/main.cpp
    src/sensor.cpp
)

target_include_directories(sensor_framework PRIVATE include)
target_compile_options(sensor_framework PRIVATE -Wall -Wextra)
