// src/appliance.cpp - MODEL CLASS definitions.
#include "appliance.h"

#include <iostream>

namespace makersplace::energy {

// TODO: once you've created include/energy_constants.h, include it and
// delete this local constant.
const int DAYS_PER_MONTH = 30;

double Appliance::tariffGhsPerKwh = 1.80;

Appliance::Appliance(std::string n, double watts, double hours)
    : name(n), powerWatts(watts > 0 ? watts : 100.0) {
    if (!useFor(hours)) {
        std::cout << "Warning: invalid hours for " << name << ", using 1 hour" << std::endl;
    }
}

Appliance::Appliance(std::string n) : Appliance(n, 100.0, 1.0) {}

bool Appliance::useFor(double hours) {
    if (hours < 0 || hours > 24) {
        return false;
    }
    hoursPerDay = hours;
    return true;
}

double Appliance::dailyKwh() const {
    return powerWatts * hoursPerDay / 1000.0;
}

double Appliance::monthlyCostGhs() const {
    return dailyKwh() * DAYS_PER_MONTH * tariffGhsPerKwh;
}

void Appliance::print() const {
    std::cout << name << ": " << powerWatts << " W x " << hoursPerDay << " h = "
              << dailyKwh() << " kWh/day, GHS " << monthlyCostGhs() << "/month" << std::endl;
}

bool Appliance::setTariff(double ghsPerKwh) {
    if (ghsPerKwh <= 0) {
        return false;
    }
    tariffGhsPerKwh = ghsPerKwh;
    return true;
}

} // namespace makersplace::energy
