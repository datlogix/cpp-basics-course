// new[] allocates an array whose size is decided at runtime.
// delete[] must be called exactly once when you're done with it.
#include <iostream>

int main() {
    int n;
    std::cout << "How many readings? ";
    std::cin >> n;

    double* readings = new double[n];

    for (int i = 0; i < n; i++) {
        readings[i] = (i + 1) * 1.5; // just fill with sample data
    }

    std::cout << "-- readings --" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << readings[i] << std::endl;
    }

    delete[] readings;
    readings = nullptr; // defensive: avoid an accidental dangling pointer

    return 0;
}
