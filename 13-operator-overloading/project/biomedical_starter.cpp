// Module 13 Project - Track C: Dosage
// See project/README.md for requirements.
#include <iostream>

class Dosage {
private:
    double milligrams;

public:
    Dosage(double mg) : milligrams(mg) {}

    Dosage operator+(const Dosage& other) const {
        // TODO: combine two doses
        return Dosage(0);
    }

    Dosage operator*(double factor) const {
        // TODO: scale this dose by factor (e.g. by patient weight in kg)
        return Dosage(0);
    }

    bool operator<(const Dosage& other) const {
        // TODO: compare milligrams
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const Dosage& d);
};

std::ostream& operator<<(std::ostream& os, const Dosage& d) {
    // TODO: print "<mg> mg"
    return os;
}

int main() {
    const Dosage MAX_SAFE_DOSE(500.0);

    Dosage morningDose(150.0);
    Dosage eveningDose(150.0);

    // TODO: compute totalToday = morningDose + eveningDose, print it.

    Dosage perKgDose(5.0);
    double patientWeightKg = 70.0;
    // TODO: compute weightBasedDose = perKgDose * patientWeightKg, print it.

    // TODO: check weightBasedDose < MAX_SAFE_DOSE and print a safety message.

    return 0;
}
