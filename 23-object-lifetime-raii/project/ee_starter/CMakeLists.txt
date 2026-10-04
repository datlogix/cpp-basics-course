cmake_minimum_required(VERSION 3.16)
project(BenchSupplyGuard LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bench_guard
    src/main.cpp
    src/power_supply.cpp
    src/supply_guard.cpp
)

target_include_directories(bench_guard PRIVATE include)
target_compile_options(bench_guard PRIVATE -Wall -Wextra)
