#include "supply_guard.h"

#include <fstream>
#include <iostream>

namespace makersplace::energy {

SupplyGuard::SupplyGuard(PowerSupply& psu, double volts) : supply(psu), testVolts(volts) {
    // TODO: print a "[+] ..." trace line and switch the supply on
}

SupplyGuard::~SupplyGuard() {
    // TODO: switch the supply off, append
    //   "test at <V> V: supply switched off safely"
    // to bench_log.txt (std::ios::app), and print a "[-] ..." trace line
}

} // namespace makersplace::energy
