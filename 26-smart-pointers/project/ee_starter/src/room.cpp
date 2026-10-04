#include "room.h"

#include <iostream>
#include <utility>

namespace makersplace::energy {

Room::Room(std::string n) : name(n) {}

Room::~Room() {
    std::cout << "  [-] room " << name << std::endl;
}

void Room::install(std::unique_ptr<Appliance> a) {
    appliances.push_back(std::move(a));
}

std::unique_ptr<Appliance> Room::remove(std::string applianceName) {
    // TODO: find it, std::move it out, erase the slot, return it (or nullptr).
    (void)applianceName;
    return nullptr;
}

double Room::dailyKwh() const {
    // TODO: sum dailyKwh() over all appliances (one polymorphic loop)
    return 0;
}

void Room::printReport() const {
    // TODO: print each appliance's name, kind and kWh/day, then the room total.
    std::cout << name << ":" << std::endl;
}

} // namespace makersplace::energy
