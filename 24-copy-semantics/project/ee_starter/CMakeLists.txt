cmake_minimum_required(VERSION 3.16)
project(WaveformProcessing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(waveform
    src/main.cpp
    src/waveform.cpp
    # TODO (Part 2): add your RAII class's .cpp file
)

target_include_directories(waveform PRIVATE include)
target_compile_options(waveform PRIVATE -Wall -Wextra)
