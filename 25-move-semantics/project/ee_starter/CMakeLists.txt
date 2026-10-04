cmake_minimum_required(VERSION 3.16)
project(SignalPipeline LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(signal_pipeline
    src/main.cpp
    src/waveform.cpp
    # TODO (Part 2): add your move-only RAII class's .cpp file
)

target_include_directories(signal_pipeline PRIVATE include)
target_compile_options(signal_pipeline PRIVATE -Wall -Wextra)
