cmake_minimum_required(VERSION 3.16)
project(ScoreModeration LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(moderation
    src/main.cpp
    src/score_sheet.cpp
    # TODO (Part 2): add your RAII class's .cpp file
)

target_include_directories(moderation PRIVATE include)
target_compile_options(moderation PRIVATE -Wall -Wextra)
