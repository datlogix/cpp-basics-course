#include "appliance.h"

#include <iostream>

namespace makersplace::energy {

Appliance::Appliance(std::string n, double watts) : name(n), powerWatts(watts) {}

Appliance::~Appliance() {
    std::cout << "  [-] appliance " << name << std::endl;
}

AlwaysOnAppliance::AlwaysOnAppliance(std::string n, double watts) : Appliance(n, watts) {}

double AlwaysOnAppliance::dailyKwh() const {
    return powerWatts * 24 / 1000.0;
}

TimedAppliance::TimedAppliance(std::string n, double watts, double hours)
    : Appliance(n, watts), hoursPerDay(hours) {}

double TimedAppliance::dailyKwh() const {
    // TODO
    return 0;
}

ThermostaticAppliance::ThermostaticAppliance(std::string n, double watts, double hours, double duty)
    : Appliance(n, watts), hoursPerDay(hours), dutyCycle(duty) {}

double ThermostaticAppliance::dailyKwh() const {
    // TODO
    return 0;
}

} // namespace makersplace::energy
