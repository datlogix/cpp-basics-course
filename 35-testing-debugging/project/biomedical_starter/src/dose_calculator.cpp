#include "dose_calculator.h"

#include <stdexcept>

namespace makersplace::clinic {

DoseCalculator::DoseCalculator(double mgPerKgValue, double maxSingleMg)
    : mgPerKg(mgPerKgValue), maxSingleDoseMg(maxSingleMg) {
    if (mgPerKg <= 0 || maxSingleDoseMg <= 0) {
        throw std::invalid_argument("dosing parameters must be positive");
    }
}

double DoseCalculator::doseMg(double weightKg) const {
    if (weightKg < 0 || weightKg > 300) {
        throw std::invalid_argument("implausible weight");
    }
    double dose = weightKg * mgPerKg;
    if (dose > maxSingleDoseMg) {
        dose = maxSingleDoseMg;
    }
    return dose;
}

} // namespace makersplace::clinic
