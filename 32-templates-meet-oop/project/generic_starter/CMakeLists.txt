cmake_minimum_required(VERSION 3.16)
project(TemplateToolkit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Template code is header-only, so only main.cpp needs compiling here.
add_executable(school_toolkit
    src/main.cpp
)

target_include_directories(school_toolkit PRIVATE include)
target_compile_options(school_toolkit PRIVATE -Wall -Wextra)
