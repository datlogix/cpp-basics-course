// assert(condition) stops the program with the file, line and condition
// if the condition is false. Good for checking your OWN assumptions.
#include <cassert>
#include <iostream>
#include <vector>

double average(const std::vector<double>& values) {
    assert(!values.empty()); // a precondition: callers must never pass an empty vector
    double total = 0;
    for (double v : values) {
        total += v;
    }
    return total / values.size();
}

int main() {
    // Using assert as a very simple test:
    assert(average({2, 4, 6}) == 4);
    assert(average({5}) == 5);
    std::cout << "All asserts passed." << std::endl;

    // Uncomment to see a failed assertion stop the program:
    // assert(average({1, 2}) == 2);
    //   -> 01_assert_basics: 01_assert_basics.cpp:NN: int main(): Assertion `average({1, 2}) == 2' failed.

    // Uncomment to see the precondition catch a misuse:
    // average({});

    // Limits of assert for testing: it stops at the FIRST failure, it can't
    // check that an exception is thrown, and compiling with -DNDEBUG switches
    // every assert off.
    return 0;
}
