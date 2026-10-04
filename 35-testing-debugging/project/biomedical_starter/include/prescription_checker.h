#pragma once

#include <map>
#include <string>
#include <vector>

namespace makersplace::clinic {

struct Prescription {
    std::string patient;
    std::string drug;
    double mgPerDose;
    int dosesPerDay;
};

class Pager {
public:
    virtual ~Pager() = default;
    virtual void page(const std::string& who, const std::string& message) = 0;
};

class PrescriptionChecker {
private:
    Pager& pager;
    std::map<std::string, double> dailyLimitMg; // drug -> maximum mg per day

public:
    explicit PrescriptionChecker(Pager& p) : pager(p) {}
    void setDailyLimit(const std::string& drug, double mg) { dailyLimitMg[drug] = mg; }

    // Pages "pharmacist" for each prescription whose daily total is ABOVE its
    // drug's limit (drugs with no limit set are not checked). Returns the count.
    int check(const std::vector<Prescription>& prescriptions);
};

} // namespace makersplace::clinic
