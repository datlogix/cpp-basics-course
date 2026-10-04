#include "model.h"

#include <iostream>
#include <memory>

using namespace makersplace::energy;

int main() {
    // Part 3 demonstration of the problem: nothing enforces the breaker rating.
    Circuit kitchenCircuit(20.0);
    kitchenCircuit.push_back(8.5);  // kettle
    kitchenCircuit.push_back(15.0); // electric cooker - should be refused!
    std::cout << "Kitchen circuit total: " << kitchenCircuit.totalAmps() << " A on a 20 A breaker"
              << std::endl;

    Room kitchen("Kitchen");
    Room lounge("Lounge");
    EnergyMeter meter;

    meter.monitor(kitchen.install(std::make_unique<Appliance>("Fridge", 150, 24)));
    meter.monitor(lounge.install(std::make_unique<Appliance>("Television", 90, 5)));
    lounge.install(std::make_unique<Appliance>("Decoder", 20, 5)); // not monitored

    std::cout << "Monitored: " << meter.dailyKwh() << " kWh/day" << std::endl;

    // TODO (Part 4): finish the scenario from the README - a House composed
    // of rooms, two Electricians and a contract switch, a BillCalculator,
    // and destroying the meter without deleting any appliance.

    std::cout << "end of main:" << std::endl;
    return 0;
}
