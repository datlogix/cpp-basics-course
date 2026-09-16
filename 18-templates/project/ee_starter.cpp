// Module 18 Project - Track B: Signal Statistics
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
        // TODO
        return 0;
    }

    T minimum() const {
        // TODO
        return T();
    }

    T maximum() const {
        // TODO
        return T();
    }

    double standardDeviation() const {
        // TODO
        return 0;
    }
};

int main() {
    const double NOISY_THRESHOLD = 0.5; // volts - justify your own choice here

    Statistics<double> voltageSamples;
    voltageSamples.addValue(2.10);
    voltageSamples.addValue(2.15);
    voltageSamples.addValue(2.08);
    voltageSamples.addValue(2.20);
    voltageSamples.addValue(2.05);

    // TODO: print mean, min, max, standard deviation.

    // TODO: compare standardDeviation() to NOISY_THRESHOLD and print
    // whether the signal is "noisy" or "stable".

    return 0;
}
