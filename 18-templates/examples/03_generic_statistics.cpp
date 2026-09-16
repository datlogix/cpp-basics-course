// A generic sum/average that works for a vector<int> or vector<double>
// with no duplicated code.
#include <iostream>
#include <vector>

template <typename T>
T computeSum(std::vector<T> values) {
    T total = T(); // zero-initialize, whatever T is
    for (T v : values) {
        total += v;
    }
    return total;
}

template <typename T>
double computeAverage(std::vector<T> values) {
    return static_cast<double>(computeSum(values)) / values.size();
}

int main() {
    std::vector<int> sampleCounts = {10, 20, 30, 40};
    std::cout << "Sum: " << computeSum(sampleCounts) << std::endl;
    std::cout << "Average: " << computeAverage(sampleCounts) << std::endl;

    std::vector<double> voltages = {2.1, 4.8, 3.3};
    std::cout << "Sum: " << computeSum(voltages) << std::endl;
    std::cout << "Average: " << computeAverage(voltages) << std::endl;

    return 0;
}
