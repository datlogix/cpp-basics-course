// Module 17 Project - Track C: Vital Sign Analyzer
// See project/README.md for requirements.
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    const double LOW_HEART_RATE = 60.0;
    const double HIGH_HEART_RATE = 100.0;
    const double HEALTHY_AVERAGE = 80.0;

    int n;
    std::cout << "How many readings? ";
    std::cin >> n;

    std::vector<double> readings(n);
    for (int i = 0; i < n; i++) {
        std::cout << "Reading " << i << ": ";
        std::cin >> readings[i];
    }

    // TODO: sort readings, print them, and print highest/lowest.

    // TODO: use count_if with captured LOW_HEART_RATE/HIGH_HEART_RATE to
    // count abnormal readings.

    // TODO: use transform to build a "risk score" vector:
    // std::abs(reading - HEALTHY_AVERAGE) for every reading.

    // TODO: find and print the reading with the highest risk score
    // using max_element on the risk-score vector.

    return 0;
}
