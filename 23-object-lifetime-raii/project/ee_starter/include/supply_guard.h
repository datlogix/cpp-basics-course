#pragma once

#include "power_supply.h"

namespace makersplace::energy {

// RAII: constructing a SupplyGuard switches the supply ON; destroying it
// switches the supply OFF - on every exit path.
class SupplyGuard {
private:
    PowerSupply& supply;
    double testVolts;

public:
    SupplyGuard(PowerSupply& psu, double volts);
    ~SupplyGuard();
};

} // namespace makersplace::energy
