#pragma once

namespace makersplace::clinic {

// Simplified for teaching - NOT for clinical use.
class DoseCalculator {
private:
    double mgPerKg;
    double maxSingleDoseMg;

public:
    DoseCalculator(double mgPerKgValue, double maxSingleMg); // both must be positive, else std::invalid_argument

    // weight must be > 0 and <= 300 kg, else std::invalid_argument.
    // Returns weightKg * mgPerKg, capped at maxSingleDoseMg.
    double doseMg(double weightKg) const;
};

} // namespace makersplace::clinic
