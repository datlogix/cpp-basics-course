// include/appliance.h - MODEL CLASS: study this, then split Room the same way.
#pragma once

#include <string>

namespace makersplace::energy {

class Appliance {
private:
    // INVARIANT: powerWatts > 0 and 0 <= hoursPerDay <= 24.
    static double tariffGhsPerKwh;

    std::string name;
    double powerWatts;
    double hoursPerDay = 1.0;

public:
    Appliance(std::string n, double watts, double hours);
    explicit Appliance(std::string n);

    bool useFor(double hours);
    double dailyKwh() const;
    double monthlyCostGhs() const;
    void print() const;

    std::string getName() const { return name; }

    static bool setTariff(double ghsPerKwh);
    static double getTariff() { return tariffGhsPerKwh; }
};

} // namespace makersplace::energy
