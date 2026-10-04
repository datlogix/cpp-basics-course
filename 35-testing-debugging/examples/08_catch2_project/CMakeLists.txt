# A Catch2 test project. From inside this folder:
#   cmake -S . -B build          (the first run downloads Catch2 - needs internet)
#   cmake --build build
#   ./build/fraction_tests       (or: ctest --test-dir build --output-on-failure)
#   ./build/fraction_demo        (the real program, sharing the same src/ code)
cmake_minimum_required(VERSION 3.16)
project(FractionWithTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.7.1
)
FetchContent_MakeAvailable(Catch2)

# The real program.
add_executable(fraction_demo src/main.cpp src/fraction.cpp)
target_include_directories(fraction_demo PRIVATE include)
target_compile_options(fraction_demo PRIVATE -Wall -Wextra)

# The tests: a SEPARATE program, built from the same fraction.cpp.
add_executable(fraction_tests tests/test_fraction.cpp src/fraction.cpp)
target_include_directories(fraction_tests PRIVATE include)
target_compile_options(fraction_tests PRIVATE -Wall -Wextra)
target_link_libraries(fraction_tests PRIVATE Catch2::Catch2WithMain) # Catch2 provides main()

enable_testing()
add_test(NAME fraction_tests COMMAND fraction_tests)
