cmake_minimum_required(VERSION 3.16)
project(CircuitLoadsTested LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CORE_SOURCES src/circuit.cpp src/load_monitor.cpp)

add_executable(loads src/main.cpp ${CORE_SOURCES})
target_include_directories(loads PRIVATE include)
target_compile_options(loads PRIVATE -Wall -Wextra)

add_executable(load_tests tests/test_loads.cpp ${CORE_SOURCES})
target_include_directories(load_tests PRIVATE include tests)
target_compile_options(load_tests PRIVATE -Wall -Wextra)

enable_testing()
add_test(NAME load_tests COMMAND load_tests)
