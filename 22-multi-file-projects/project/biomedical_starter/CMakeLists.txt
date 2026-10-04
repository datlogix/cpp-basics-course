cmake_minimum_required(VERSION 3.16)
project(ClinicAppointments LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(clinic
    src/main.cpp
    src/patient.cpp
    # TODO: add src/doctor.cpp here once you've created it
)

target_include_directories(clinic PRIVATE include)
target_compile_options(clinic PRIVATE -Wall -Wextra)
