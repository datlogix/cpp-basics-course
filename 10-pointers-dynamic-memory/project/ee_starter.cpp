// Module 10 Project - Track B: ADC Sample Buffer
// See project/README.md for requirements.
#include <iostream>

int main() {
    const double OVER_VOLTAGE_THRESHOLD = 4.5;

    int n;
    std::cout << "How many samples? ";
    std::cin >> n;

    // TODO: dynamically allocate a double[n] buffer for voltage samples.

    // TODO: read n voltage readings from the user.

    // TODO: compute and print min, max (peak), and average voltage.

    // TODO (stretch): count and print how many samples exceeded
    // OVER_VOLTAGE_THRESHOLD.

    // TODO: delete[] the buffer and set the pointer to nullptr.

    return 0;
}
