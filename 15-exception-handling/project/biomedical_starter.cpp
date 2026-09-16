// Module 15 Project - Track C: Dosage Safety Checker
// See project/README.md for requirements.
#include <iostream>
#include <stdexcept>

class Dosage {
private:
    double milligrams;

public:
    Dosage(double mg) {
        if (mg < 0) {
            throw std::invalid_argument("Dosage cannot be negative.");
        }
        milligrams = mg;
    }

    double getMilligrams() const { return milligrams; }
};

int main() {
    const double MAX_SAFE_DOSE_MG = 500.0;

    int succeeded = 0;
    int rejected = 0;

    std::cout << "Enter patient weight (kg) and dose rate (mg/kg). Enter weight -1 to stop." << std::endl;

    while (true) {
        double weightKg, ratePerKg;
        std::cout << "Weight (kg): ";
        std::cin >> weightKg;
        if (weightKg == -1) break;
        std::cout << "Rate (mg/kg): ";
        std::cin >> ratePerKg;

        try {
            double totalDoseMg = weightKg * ratePerKg;
            Dosage dose(totalDoseMg); // may throw std::invalid_argument

            // TODO: throw std::runtime_error("Dose exceeds maximum safe amount!")
            // if dose.getMilligrams() exceeds MAX_SAFE_DOSE_MG.

            std::cout << "Prescribed dose: " << dose.getMilligrams() << " mg" << std::endl;
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
