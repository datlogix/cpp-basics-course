// max_element/min_element return an ITERATOR - dereference with * to
// get the actual value.
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<double> voltages = {2.1, 4.8, 3.3, 5.0, 1.9};

    auto peakIt = std::max_element(voltages.begin(), voltages.end());
    auto lowIt = std::min_element(voltages.begin(), voltages.end());

    std::cout << "Peak: " << *peakIt << std::endl;
    std::cout << "Lowest: " << *lowIt << std::endl;

    return 0;
}
