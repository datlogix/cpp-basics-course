// Module 17 Project - Track B: Waveform Analyzer
// See project/README.md for requirements.
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    const double OVER_VOLTAGE_THRESHOLD = 4.5;

    int n;
    std::cout << "How many samples? ";
    std::cin >> n;

    std::vector<int> rawSamples(n);
    for (int i = 0; i < n; i++) {
        std::cout << "Raw ADC sample " << i << " (0-1023): ";
        std::cin >> rawSamples[i];
    }

    // TODO: use transform to convert rawSamples to a vector<double> of
    // voltages in the range 0.0-5.0 (raw / 1023.0 * 5.0).

    // TODO: sort the voltages, print them, and print the peak (max) and
    // lowest (min) voltage.

    // TODO: use count_if with a captured OVER_VOLTAGE_THRESHOLD to count
    // over-voltage events.

    return 0;
}
