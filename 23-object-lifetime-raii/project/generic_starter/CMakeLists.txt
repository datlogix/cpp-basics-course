cmake_minimum_required(VERSION 3.16)
project(ClubAttendance LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(club_attendance
    src/main.cpp
    src/student.cpp
    src/attendance_session.cpp
)

target_include_directories(club_attendance PRIVATE include)
target_compile_options(club_attendance PRIVATE -Wall -Wextra)
