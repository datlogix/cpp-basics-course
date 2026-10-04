// Exercise 1: Testing & Debugging OO Code
//
// TemperatureLog below was written WITHOUT tests. It contains exactly one
// bug. Your job: write tests that describe how it SHOULD behave, let the
// tests find the bug, then fix it.
//
// The specification:
//   - addReading(c) stores a reading; readings outside -40..125 C throw
//     std::out_of_range and are NOT stored.
//   - count() is the number of stored readings.
//   - highest() and lowest() return the extreme readings; on an empty log
//     they throw std::logic_error.
//   - averageOfLast(n) is the average of the most recent n readings
//     (all of them if n > count()); it throws std::invalid_argument if
//     n <= 0, and std::logic_error if the log is empty.
//
// TODO 1: Using minitest.h (Arrange-Act-Assert, one behaviour per
//         testCase), write tests covering EVERY line of the specification,
//         including boundaries (-40, 125, 125.1) and the state of the log
//         after a rejected reading.
// TODO 2: Build with sanitizers and run:
//           g++ -std=c++17 -Wall -Wextra -g -fsanitize=address,undefined exercise1.cpp -o exercise1
//           ./exercise1
//         One of your tests should FAIL. Write down which one in a comment.
// TODO 3: Use the failure message (and gdb, if you like) to find the bug.
//         Fix it, and re-run: every test must pass.
// TODO 4: Add one test for a behaviour the specification does NOT
//         mention but you think matters. Explain it in a comment.
#include "../examples/minitest.h"

#include <stdexcept>
#include <vector>

class TemperatureLog {
private:
    std::vector<double> readings;

public:
    void addReading(double c) {
        if (c < -40 || c > 125) {
            throw std::out_of_range("reading outside sensor range");
        }
        readings.push_back(c);
    }

    int count() const { return static_cast<int>(readings.size()); }

    double highest() const {
        if (readings.empty()) throw std::logic_error("empty log");
        double best = readings[0];
        for (double r : readings) if (r > best) best = r;
        return best;
    }

    double lowest() const {
        if (readings.empty()) throw std::logic_error("empty log");
        double best = readings[0];
        for (double r : readings) if (r < best) best = r;
        return best;
    }

    double averageOfLast(int n) const {
        if (n <= 0) throw std::invalid_argument("n must be positive");
        if (readings.empty()) throw std::logic_error("empty log");
        if (n > count()) n = count();
        double total = 0;
        for (int i = count() - n; i < count() - 1; i++) {
            total += readings[i];
        }
        return total / n;
    }
};

int main() {
    // TODO 1: your tests here

    return TEST_SUMMARY();
}
