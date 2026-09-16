// Module 18 Project - Track A: Grade Statistics
// See project/README.md for requirements.
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

template <typename T>
class Statistics {
private:
    std::vector<T> values;

public:
    void addValue(T v) {
        values.push_back(v);
    }

    double mean() const {
        // TODO: sum of values / count, guard against an empty vector
        return 0;
    }

    T minimum() const {
        // TODO: use std::min_element
        return T();
    }

    T maximum() const {
        // TODO: use std::max_element
        return T();
    }

    double standardDeviation() const {
        // TODO:
        // 1. compute m = mean()
        // 2. sum of (v - m) * (v - m) for every v in values
        // 3. return sqrt(sum / values.size())
        return 0;
    }
};

int main() {
    Statistics<double> examScores;
    examScores.addValue(72.0);
    examScores.addValue(88.0);
    examScores.addValue(65.0);
    examScores.addValue(91.0);
    examScores.addValue(78.0);

    // TODO: print mean, min, max, standard deviation.

    // TODO: print a sentence interpreting the standard deviation
    // (clustered vs. spread out).

    return 0;
}
