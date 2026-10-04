#include "energy_controller.h"

int main() {
    EnergyController home;
    home.add("Fridge", "fridge", 150, 24, 1);
    home.add("Security lights", "lighting", 60, 12, 1);
    home.add("Air conditioner", "aircon", 1500, 8, 3);
    home.add("Borehole pump", "pump", 750, 2, 2);
    home.add("Lounge lights", "lighting", 40, 6, 2);

    home.runDay(2.0);

    home.tariffBand = "commercial";
    home.runDay(5.0);
    return 0;
}
