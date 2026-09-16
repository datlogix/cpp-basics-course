// Module 18 Project - Track C: Vital Sign Statistics
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
    const double INSTABILITY_THRESHOLD = 8.0; // bpm - justify your own choice here

    Statistics<double> heartRateReadings;
    heartRateReadings.addValue(72.0);
    heartRateReadings.addValue(75.0);
    heartRateReadings.addValue(70.0);
    heartRateReadings.addValue(90.0);
    heartRateReadings.addValue(68.0);

    // TODO: print mean, min, max, standard deviation.

    // TODO: compare standardDeviation() to INSTABILITY_THRESHOLD and
    // print a flag message if it's exceeded.

    return 0;
}
