// TODO (README requirement 5): Why must the SupplyGuard be an automatic
// (stack) object, not one created with new?
//
#include "power_supply.h"
#include "supply_guard.h"

#include <iostream>

using makersplace::energy::PowerSupply;
using makersplace::energy::SupplyGuard;

const double MAX_CURRENT_AMPS = 2.0;

void testAppliance(PowerSupply& psu, double volts, double ohms) {
    std::cout << "Testing " << ohms << " ohm load at " << volts << " V" << std::endl;
    // TODO: create a SupplyGuard, then:
    //   - ohms <= 0              -> print "short circuit!" and RETURN EARLY
    //   - volts / ohms > MAX     -> print "overcurrent!" and RETURN EARLY
    //   - otherwise print the current and the power P = V * I
    (void)psu;
}

int main() {
    PowerSupply psu;
    testAppliance(psu, 12.0, 24.0); // 0.5 A - fine
    testAppliance(psu, 12.0, 0.0);  // short circuit
    testAppliance(psu, 24.0, 4.0);  // 6 A - overcurrent

    std::cout << "Supply is " << (psu.isOn() ? "STILL ON (bug!)" : "off") << std::endl;
    return 0;
}
