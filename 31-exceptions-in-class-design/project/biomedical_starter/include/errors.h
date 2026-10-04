#pragma once

#include <stdexcept>
#include <string>

namespace makersplace::clinic {

class ClinicalError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class DoseLimitError : public ClinicalError {
private:
    std::string drug;
    double requestedMgPerDay;
    double maxMgPerDay;

public:
    DoseLimitError(std::string d, double requested, double max)
        : ClinicalError(d + ": " + std::to_string(requested) + " mg/day exceeds the maximum of " +
                        std::to_string(max) + " mg/day"),
          drug(d), requestedMgPerDay(requested), maxMgPerDay(max) {}
    std::string getDrug() const { return drug; }
    double getRequested() const { return requestedMgPerDay; }
    double getMaximum() const { return maxMgPerDay; }
};

// TODO: AllergyConflictError (carries the allergen), PatientNotFoundError,
// CorruptRecordError

} // namespace makersplace::clinic
