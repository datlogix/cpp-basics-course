#include "infusion_pump.h"

#include <iostream>

namespace makersplace::clinic {

void InfusionPump::start(double rate) {
    rateMlPerHour = rate;
    running = true;
    std::cout << "    PUMP STARTED at " << rateMlPerHour << " mL/h" << std::endl;
}

void InfusionPump::stop() {
    running = false;
    rateMlPerHour = 0;
    std::cout << "    PUMP STOPPED" << std::endl;
}

} // namespace makersplace::clinic
