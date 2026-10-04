#include "power_supply.h"

#include <iostream>

namespace makersplace::energy {

void PowerSupply::switchOn(double v) {
    volts = v;
    on = true;
    std::cout << "    PSU ON at " << volts << " V" << std::endl;
}

void PowerSupply::switchOff() {
    on = false;
    volts = 0;
    std::cout << "    PSU OFF" << std::endl;
}

} // namespace makersplace::energy
