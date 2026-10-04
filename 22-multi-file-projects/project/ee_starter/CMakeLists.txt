cmake_minimum_required(VERSION 3.16)
project(HomeEnergyMonitor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(energy_monitor
    src/main.cpp
    src/appliance.cpp
    # TODO: add src/room.cpp here once you've created it
)

target_include_directories(energy_monitor PRIVATE include)
target_compile_options(energy_monitor PRIVATE -Wall -Wextra)
