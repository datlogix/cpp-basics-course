// Module 10 Project - Track C: Vital Sign Buffer
// See project/README.md for requirements.
#include <iostream>

int main() {
    const double LOW_HEART_RATE = 60.0;
    const double HIGH_HEART_RATE = 100.0;

    int n;
    std::cout << "How many readings in this session? ";
    std::cin >> n;

    // TODO: dynamically allocate a double[n] buffer for heart-rate readings.

    // TODO: read n heart-rate readings from the user.

    // TODO: compute and print min, max, and average heart rate.

    // TODO (stretch): count and print how many readings fell outside
    // [LOW_HEART_RATE, HIGH_HEART_RATE] as "abnormal."

    // TODO: delete[] the buffer and set the pointer to nullptr.

    return 0;
}
