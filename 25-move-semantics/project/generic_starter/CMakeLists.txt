cmake_minimum_required(VERSION 3.16)
project(TermArchive LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(term_archive
    src/main.cpp
    src/score_sheet.cpp
    # TODO (Part 2): add your move-only RAII class's .cpp file
)

target_include_directories(term_archive PRIVATE include)
target_compile_options(term_archive PRIVATE -Wall -Wextra)
