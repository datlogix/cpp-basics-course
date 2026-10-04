# A minimal CMake project. Build it from inside this folder with:
#   cmake -S . -B build
#   cmake --build build
#   ./build/energy_report
cmake_minimum_required(VERSION 3.16)
project(EnergyReport LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(energy_report
    src/main.cpp
    src/appliance.cpp
)

target_include_directories(energy_report PRIVATE include)
target_compile_options(energy_report PRIVATE -Wall -Wextra)
