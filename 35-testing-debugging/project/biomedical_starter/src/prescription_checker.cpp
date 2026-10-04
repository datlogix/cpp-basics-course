#include "prescription_checker.h"

namespace makersplace::clinic {

int PrescriptionChecker::check(const std::vector<Prescription>& prescriptions) {
    int pages = 0;
    for (const Prescription& p : prescriptions) {
        auto limit = dailyLimitMg.find(p.drug);
        if (limit == dailyLimitMg.end()) {
            continue;
        }
        double daily = p.mgPerDose * p.dosesPerDay;
        if (daily > limit->second) {
            pager.page("pharmacist", p.patient + ": " + p.drug + " " + std::to_string(daily) + " mg/day over limit");
            pages++;
        }
    }
    return pages;
}

} // namespace makersplace::clinic
