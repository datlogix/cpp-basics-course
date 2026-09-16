// throw signals a problem; try/catch responds to it instead of crashing.
#include <iostream>
#include <stdexcept>

double computeOhmsLawCurrent(double voltage, double resistance) {
    if (resistance <= 0) {
        throw std::invalid_argument("Resistance must be positive.");
    }
    return voltage / resistance;
}

int main() {
    try {
        double current = computeOhmsLawCurrent(12.0, 0.0);
        std::cout << "Current: " << current << std::endl; // never reached
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::cout << "Program continues normally after the error." << std::endl;

    return 0;
}
