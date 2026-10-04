cmake_minimum_required(VERSION 3.16)
project(SmartHomeWiring LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO (Part 2): once you've split model.h into one file per class,
# list every .cpp file here.
add_executable(smart_home
    src/main.cpp
    src/model.cpp
)

target_include_directories(smart_home PRIVATE include)
target_compile_options(smart_home PRIVATE -Wall -Wextra)
