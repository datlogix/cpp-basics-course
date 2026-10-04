cmake_minimum_required(VERSION 3.16)
project(FeeAccountsTested LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The code under test, shared by both programs.
set(CORE_SOURCES src/fee_account.cpp src/fee_reminder.cpp)

add_executable(fees src/main.cpp ${CORE_SOURCES})
target_include_directories(fees PRIVATE include)
target_compile_options(fees PRIVATE -Wall -Wextra)

add_executable(fee_tests tests/test_fees.cpp ${CORE_SOURCES})
target_include_directories(fee_tests PRIVATE include tests)
target_compile_options(fee_tests PRIVATE -Wall -Wextra)

enable_testing()
add_test(NAME fee_tests COMMAND fee_tests)
