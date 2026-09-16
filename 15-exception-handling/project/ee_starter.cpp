// Module 15 Project - Track B: Circuit Safety Checker
// See project/README.md for requirements.
#include <iostream>
#include <stdexcept>

double computeCurrent(double voltage, double resistance) {
    if (resistance <= 0) {
        throw std::invalid_argument("Resistance must be positive.");
    }
    return voltage / resistance;
}

int main() {
    const double MAX_SAFE_CURRENT = 5.0;

    int succeeded = 0;
    int rejected = 0;

    std::cout << "Enter voltage and resistance. Enter voltage -1 to stop." << std::endl;

    while (true) {
        double voltage, resistance;
        std::cout << "Voltage: ";
        std::cin >> voltage;
        if (voltage == -1) break;
        std::cout << "Resistance: ";
        std::cin >> resistance;

        try {
            double current = computeCurrent(voltage, resistance);

            // TODO: throw std::runtime_error("Overcurrent condition!")
            // if current exceeds MAX_SAFE_CURRENT.

            std::cout << "Current: " << current << " A" << std::endl;
            succeeded++;
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input: " << e.what() << std::endl;
            rejected++;
        } catch (const std::runtime_error& e) {
            std::cout << "Safety error: " << e.what() << std::endl;
            rejected++;
        }
    }

    std::cout << "Succeeded: " << succeeded << ", Rejected: " << rejected << std::endl;

    return 0;
}
