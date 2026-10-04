cmake_minimum_required(VERSION 3.16)
project(HomeOwnership LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(home_ownership
    src/main.cpp
    src/appliance.cpp
    src/room.cpp
    src/house.cpp
)

target_include_directories(home_ownership PRIVATE include)
target_compile_options(home_ownership PRIVATE -Wall -Wextra)
