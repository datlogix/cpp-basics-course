cmake_minimum_required(VERSION 3.16)
project(EnergyRefactor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO: list your new .cpp files here as you extract classes.
add_executable(energy_refactor
    src/main.cpp
    src/energy_controller.cpp
)

target_include_directories(energy_refactor PRIVATE include)
target_compile_options(energy_refactor PRIVATE -Wall -Wextra)
