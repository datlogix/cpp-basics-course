// OWNERSHIP MAP (Part 4, step 10): for every pointer-like member or
// parameter, say whether it OWNS, SHARES, OBSERVES or BORROWS, and why.
//
#include "house.h"

#include <iostream>
#include <memory>

using namespace makersplace::energy; // fine in a .cpp file's main - never in a header

int main() {
    House home;
    std::shared_ptr<Room> kitchen = home.addRoom("Kitchen");
    std::shared_ptr<Room> lounge = home.addRoom("Lounge");
    std::shared_ptr<Room> boysQuarters = home.addRoom("Boys' quarters");

    kitchen->install(std::make_unique<AlwaysOnAppliance>("Fridge", 150));
    kitchen->install(std::make_unique<TimedAppliance>("Microwave", 1100, 0.3));
    lounge->install(std::make_unique<TimedAppliance>("Television", 90, 5));
    lounge->install(std::make_unique<ThermostaticAppliance>("Air conditioner", 1500, 8, 0.6));
    boysQuarters->install(std::make_unique<TimedAppliance>("Ceiling fan", 75, 10));

    kitchen->printReport();
    lounge->printReport();

    // TODO (Part 2): move the Television from the lounge to the kitchen
    // with remove() and install(), then print both reports again.

    SmartPlug plug(boysQuarters);
    boysQuarters.reset(); // only the House owns it now
    plug.report();
    home.demolish("Boys' quarters"); // TODO (Part 3): the room should be deleted here...
    plug.report();                   // ...and the plug should notice

    kitchen.reset();
    lounge.reset();
    std::cout << "end of main:" << std::endl;
    return 0;
}
