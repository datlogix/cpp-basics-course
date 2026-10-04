#include "model.h"

#include <iostream>
#include <utility>

namespace makersplace::energy {

double Circuit::totalAmps() const {
    double total = 0;
    for (double a : *this) {
        total += a;
    }
    return total;
}

Appliance::Appliance(std::string n, double watts, double hours)
    : name(n), powerWatts(watts), hoursPerDay(hours) {}
Appliance::~Appliance() { std::cout << "  [-] appliance " << name << std::endl; }

Room::Room(std::string n) : name(n) {}
Room::~Room() { std::cout << "  [-] room " << name << std::endl; }

Appliance& Room::install(std::unique_ptr<Appliance> a) {
    appliances.push_back(std::move(a));
    return *appliances.back();
}

void EnergyMeter::monitor(const Appliance& a) {
    monitored.push_back(&a);
}

double EnergyMeter::dailyKwh() const {
    double total = 0;
    for (const Appliance* a : monitored) {
        total += a->dailyKwh();
    }
    return total;
}

} // namespace makersplace::energy
