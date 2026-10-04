cmake_minimum_required(VERSION 3.16)
project(Gradebook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(gradebook main.cpp gradebook.cpp)
target_compile_options(gradebook PRIVATE -Wall -Wextra)
