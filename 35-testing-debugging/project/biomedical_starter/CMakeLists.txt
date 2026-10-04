cmake_minimum_required(VERSION 3.16)
project(DoseCalculationTested LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CORE_SOURCES src/dose_calculator.cpp src/prescription_checker.cpp)

add_executable(doses src/main.cpp ${CORE_SOURCES})
target_include_directories(doses PRIVATE include)
target_compile_options(doses PRIVATE -Wall -Wextra)

add_executable(dose_tests tests/test_doses.cpp ${CORE_SOURCES})
target_include_directories(dose_tests PRIVATE include tests)
target_compile_options(dose_tests PRIVATE -Wall -Wextra)

enable_testing()
add_test(NAME dose_tests COMMAND dose_tests)
