cmake_minimum_required(VERSION 3.16)
project(InfusionSessions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(infusion
    src/main.cpp
    src/infusion_pump.cpp
    src/infusion_session.cpp
)

target_include_directories(infusion PRIVATE include)
target_compile_options(infusion PRIVATE -Wall -Wextra)
