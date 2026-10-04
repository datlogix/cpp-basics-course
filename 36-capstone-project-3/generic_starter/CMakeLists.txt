# Capstone 3 - MakersPlace Academy Management System
#   cmake -S . -B build
#   cmake --build build
#   ./build/app --demo
#   ctest --test-dir build --output-on-failure
# For the Stage 4 sanitizer build:
#   cmake -S . -B build-asan -DCMAKE_CXX_FLAGS="-g -fsanitize=address,undefined"
cmake_minimum_required(VERSION 3.16)
project(Capstone3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Every .cpp file EXCEPT main.cpp goes here, so the app and the tests share them.
# TODO: add each new class's .cpp file as you create it.
set(CORE_SOURCES
    src/person.cpp
    src/money.cpp
)

add_executable(app src/main.cpp ${CORE_SOURCES})
target_include_directories(app PRIVATE include)
target_compile_options(app PRIVATE -Wall -Wextra)

add_executable(tests tests/test_main.cpp ${CORE_SOURCES})
target_include_directories(tests PRIVATE include tests)
target_compile_options(tests PRIVATE -Wall -Wextra)

enable_testing()
add_test(NAME capstone_tests COMMAND tests)
