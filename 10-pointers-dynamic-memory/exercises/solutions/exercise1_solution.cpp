#include <iostream>

int main() {
    int temperature = 20;
    int* tempPtr = &temperature;
    std::cout << "temperature via pointer: " << *tempPtr << std::endl;

    *tempPtr = 25;
    std::cout << "temperature after writing through pointer: " << temperature << std::endl;

    int n;
    std::cout << "How many readings? ";
    std::cin >> n;

    double* readings = new double[n];
    for (int i = 0; i < n; i++) {
        std::cout << "Reading " << i << ": ";
        std::cin >> readings[i];
    }

    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += readings[i];
    }
    std::cout << "Average: " << sum / n << std::endl;

    delete[] readings;
    readings = nullptr;

    return 0;
}
