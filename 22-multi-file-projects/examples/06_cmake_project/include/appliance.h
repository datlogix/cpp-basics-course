// include/appliance.h
#pragma once

#include <string>

namespace makersplace::energy {

class Appliance {
private:
    std::string name;
    double powerWatts;
    double hoursPerDay;

public:
    Appliance(std::string n, double watts, double hours);
    double dailyKwh() const;
    std::string getName() const { return name; }
};

} // namespace makersplace::energy
