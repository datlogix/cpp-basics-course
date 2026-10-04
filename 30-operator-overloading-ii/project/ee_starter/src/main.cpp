#include "impedance.h"

#include <iostream>
#include <sstream>

using namespace makersplace::energy;

int main() {
    Impedance resistor(100, 0);
    Impedance inductor(0, 37.7);  // 100 mH at 60 Hz
    std::cout << "R + L in series: " << resistor + inductor << std::endl;

    Network net;
    net["R1"] = ComponentSpec{'R', 100};
    net["L1"] = ComponentSpec{'L', 0.1};
    net["C1"] = ComponentSpec{'C', 0.0001};

    // TODO: complex * and / , and the parallel() combination of R1 and C1
    // TODO: 2.0 * resistor  and  resistor * 2.0
    // TODO: read impedances from std::istringstream("50 -20 75 x")
    // TODO: std::transform the network's components into Impedances at 50 Hz
    //       with ImpedanceAt, then sort them with ByMagnitude
    // TODO: show net["X9"] throwing through a const Network&
    return 0;
}
