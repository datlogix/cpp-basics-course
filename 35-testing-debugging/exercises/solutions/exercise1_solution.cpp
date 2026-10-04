#include "../../examples/minitest.h"

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
        // BUG FIXED: the loop condition was  i < count() - 1, which skipped
        // the most recent reading. The failing test was
        // "averageOfLast(n) averages the most recent n readings".
        for (int i = count() - n; i < count(); i++) {
            total += readings[i];
        }
        return total / n;
    }
};

int main() {
    minitest::testCase("a new log is empty");
    {
        TemperatureLog log;
        CHECK_EQ(log.count(), 0);
    }

    minitest::testCase("readings inside the range are stored");
    {
        TemperatureLog log;
        log.addReading(21.5);
        log.addReading(-40);  // boundary
        log.addReading(125);  // boundary
        CHECK_EQ(log.count(), 3);
    }

    minitest::testCase("readings outside the range throw and are not stored");
    {
        TemperatureLog log;
        log.addReading(20);
        CHECK_THROWS(log.addReading(125.1), std::out_of_range);
        CHECK_THROWS(log.addReading(-40.1), std::out_of_range);
        CHECK_EQ(log.count(), 1);
        CHECK_EQ(log.highest(), 20.0);
    }

    minitest::testCase("highest and lowest find the extremes");
    {
        TemperatureLog log;
        for (double c : {24.0, 31.5, 18.25, 27.0}) log.addReading(c);
        CHECK_EQ(log.highest(), 31.5);
        CHECK_EQ(log.lowest(), 18.25);
    }

    minitest::testCase("highest and lowest throw on an empty log");
    {
        TemperatureLog log;
        CHECK_THROWS(log.highest(), std::logic_error);
        CHECK_THROWS(log.lowest(), std::logic_error);
    }

    minitest::testCase("averageOfLast(n) averages the most recent n readings");
    {
        TemperatureLog log;
        for (double c : {10.0, 20.0, 30.0, 40.0}) log.addReading(c);
        CHECK_EQ(log.averageOfLast(2), 35.0); // FAILED before the fix: got 15
        CHECK_EQ(log.averageOfLast(1), 40.0); // FAILED before the fix: got 0
    }

    minitest::testCase("averageOfLast(n) with n larger than the log uses every reading");
    {
        TemperatureLog log;
        for (double c : {10.0, 20.0}) log.addReading(c);
        CHECK_EQ(log.averageOfLast(10), 15.0);
    }

    minitest::testCase("averageOfLast rejects n <= 0 and an empty log");
    {
        TemperatureLog log;
        CHECK_THROWS(log.averageOfLast(1), std::logic_error);
        log.addReading(20);
        CHECK_THROWS(log.averageOfLast(0), std::invalid_argument);
        CHECK_THROWS(log.averageOfLast(-3), std::invalid_argument);
    }

    // TODO 4 example: the spec doesn't say what happens with repeated values.
    // Duplicates are real (a stable room temperature), so they must all count.
    minitest::testCase("duplicate readings are all stored and counted");
    {
        TemperatureLog log;
        for (int i = 0; i < 3; i++) log.addReading(22.0);
        CHECK_EQ(log.count(), 3);
        CHECK_EQ(log.averageOfLast(3), 22.0);
    }

    return TEST_SUMMARY();
}
