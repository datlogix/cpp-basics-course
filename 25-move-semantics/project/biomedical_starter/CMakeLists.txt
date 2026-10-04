cmake_minimum_required(VERSION 3.16)
project(EcgHandover LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ecg_handover
    src/main.cpp
    src/ecg_trace.cpp
    # TODO (Part 2): add your move-only RAII class's .cpp file
)

target_include_directories(ecg_handover PRIVATE include)
target_compile_options(ecg_handover PRIVATE -Wall -Wextra)
