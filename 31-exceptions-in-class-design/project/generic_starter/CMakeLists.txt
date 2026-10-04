cmake_minimum_required(VERSION 3.16)
project(ExceptionSafeCore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(enrolment
    src/main.cpp
    src/registrar.cpp
)

target_include_directories(enrolment PRIVATE include)
target_compile_options(enrolment PRIVATE -Wall -Wextra)
