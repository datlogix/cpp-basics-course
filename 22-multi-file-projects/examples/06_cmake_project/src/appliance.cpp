// src/appliance.cpp
#include "appliance.h" // found because CMakeLists.txt adds include/ to the search path

namespace makersplace::energy {

Appliance::Appliance(std::string n, double watts, double hours)
    : name(n), powerWatts(watts), hoursPerDay(hours) {}

double Appliance::dailyKwh() const {
    return powerWatts * hoursPerDay / 1000.0;
}

} // namespace makersplace::energy
