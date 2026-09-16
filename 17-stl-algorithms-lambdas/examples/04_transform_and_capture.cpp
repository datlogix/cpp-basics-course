// transform builds a new sequence by applying a lambda to every
// element. Capturing a variable lets the lambda use it.
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> rawAdcCounts = {0, 512, 1023};
    std::vector<double> voltages(rawAdcCounts.size()); // pre-sized destination

    std::transform(rawAdcCounts.begin(), rawAdcCounts.end(), voltages.begin(),
        [](int raw) { return raw / 1023.0 * 5.0; });

    std::cout << "-- converted voltages --" << std::endl;
    for (double v : voltages) {
        std::cout << v << std::endl;
    }

    double threshold = 4.5;
    int numOverThreshold = std::count_if(voltages.begin(), voltages.end(),
        [threshold](double v) { return v > threshold; }); // capture by value

    std::cout << "Over threshold: " << numOverThreshold << std::endl;

    return 0;
}
