// TODO (README step 7): If I change only src/room.cpp, which files does
// CMake recompile, and why?
//
#include "appliance.h"
// TODO: #include "room.h"

int main() {
    using makersplace::energy::Appliance;

    Appliance fridge("Fridge", 150, 24);
    Appliance fan("Ceiling fan", 75, 10);
    fridge.print();
    fan.print();

    // TODO: build Rooms (from include/room.h) containing appliances, and
    // print a per-room report with total kWh/day and monthly cost.

    return 0;
}
