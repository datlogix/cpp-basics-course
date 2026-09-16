// Throwing inside a constructor makes it impossible to create an
// invalid object in the first place.
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
    try {
        Dosage valid(150.0);
        std::cout << "Valid dosage: " << valid.getMilligrams() << " mg" << std::endl;

        Dosage invalid(-50.0); // throws - construction never completes
        std::cout << "This line never runs." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Could not create dosage: " << e.what() << std::endl;
    }

    return 0;
}
