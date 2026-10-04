cmake_minimum_required(VERSION 3.16)
project(ExceptionSafeCore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(medication_orders
    src/main.cpp
    src/medication_record.cpp
)

target_include_directories(medication_orders PRIVATE include)
target_compile_options(medication_orders PRIVATE -Wall -Wextra)
