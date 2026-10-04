cmake_minimum_required(VERSION 3.16)
project(ExceptionSafeCore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(load_switching
    src/main.cpp
    src/panel.cpp
)

target_include_directories(load_switching PRIVATE include)
target_compile_options(load_switching PRIVATE -Wall -Wextra)
