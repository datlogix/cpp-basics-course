cmake_minimum_required(VERSION 3.16)
project(ReportCards LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(report_cards
    src/main.cpp
    src/assessment.cpp
)

target_include_directories(report_cards PRIVATE include)
target_compile_options(report_cards PRIVATE -Wall -Wextra)
