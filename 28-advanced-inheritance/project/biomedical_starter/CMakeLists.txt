cmake_minimum_required(VERSION 3.16)
project(WearableMonitors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(wearables
    src/main.cpp
    src/devices.cpp
)

target_include_directories(wearables PRIVATE include)
target_compile_options(wearables PRIVATE -Wall -Wextra)
