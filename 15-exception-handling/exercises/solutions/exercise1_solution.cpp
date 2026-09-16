#include <iostream>
#include <stdexcept>
#include <vector>

double safeDivide(double a, double b) {
    if (b == 0) {
        throw std::invalid_argument("Cannot divide by zero.");
    }
    return a / b;
}

int safeAt(std::vector<int> values, int index) {
    return values.at(index); // throws std::out_of_range automatically if invalid
}

int main() {
    try {
        std::cout << safeDivide(10, 2) << std::endl;
        std::cout << safeDivide(10, 0) << std::endl; // throws
    } catch (const std::invalid_argument& e) {
        std::cout << "Division error: " << e.what() << std::endl;
    }

    std::vector<int> values = {10, 20, 30};

    try {
        std::cout << safeAt(values, 1) << std::endl;
        std::cout << safeAt(values, 10) << std::endl; // throws
    } catch (const std::out_of_range& e) {
        std::cout << "Index error: " << e.what() << std::endl;
    }

    return 0;
}
