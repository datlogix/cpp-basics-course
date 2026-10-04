// minitest.h - a deliberately tiny unit-test framework, to show there is
// no magic in real ones like Catch2 or GoogleTest.
//
//   minitest::testCase("name");          prints a heading for a group of checks
//   CHECK(condition);                     passes if condition is true
//   CHECK_EQ(actual, expected);           passes if actual == expected (prints both if not)
//   CHECK_THROWS(statement, ExceptionType);  passes if statement throws ExceptionType
//   return TEST_SUMMARY();                prints totals; returns 1 if anything failed
//
// The checks are MACROS so they can capture the text of the condition
// (#cond turns code into a string) and the file and line where they were
// written (__FILE__ and __LINE__).
#pragma once

#include <iostream>
#include <sstream>
#include <string>

namespace minitest {

inline int& passedCount() {
    static int n = 0; // a static local: one counter for the whole program
    return n;
}

inline int& failedCount() {
    static int n = 0;
    return n;
}

inline void testCase(const std::string& name) {
    std::cout << "TEST: " << name << std::endl;
}

inline void report(bool ok, const std::string& what, const char* file, int line, const std::string& detail) {
    if (ok) {
        passedCount()++;
        return;
    }
    failedCount()++;
    std::cout << "  FAIL " << file << ":" << line << ": " << what;
    if (!detail.empty()) {
        std::cout << " - " << detail;
    }
    std::cout << std::endl;
}

inline int summary() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << passedCount() << " checks passed, " << failedCount() << " failed" << std::endl;
    return failedCount() == 0 ? 0 : 1; // non-zero exit code = failure, for scripts and CI
}

} // namespace minitest

#define CHECK(cond) minitest::report(static_cast<bool>(cond), "CHECK(" #cond ")", __FILE__, __LINE__, "")

#define CHECK_EQ(actual, expected)                                                                         \
    do {                                                                                                   \
        auto mtActual = (actual);                                                                          \
        auto mtExpected = (expected);                                                                      \
        std::ostringstream mtDetail;                                                                       \
        mtDetail << "got " << mtActual << ", expected " << mtExpected;                                     \
        minitest::report(mtActual == mtExpected, "CHECK_EQ(" #actual ", " #expected ")", __FILE__, __LINE__, \
                         mtDetail.str());                                                                  \
    } while (false)

#define CHECK_THROWS(statement, ExceptionType)                                                             \
    do {                                                                                                   \
        bool mtThrown = false;                                                                             \
        try {                                                                                              \
            statement;                                                                                     \
        } catch (const ExceptionType&) {                                                                   \
            mtThrown = true;                                                                               \
        } catch (...) {                                                                                    \
        }                                                                                                  \
        minitest::report(mtThrown, "CHECK_THROWS(" #statement ", " #ExceptionType ")", __FILE__, __LINE__, \
                         "the expected exception was not thrown");                                         \
    } while (false)

#define TEST_SUMMARY() minitest::summary()
