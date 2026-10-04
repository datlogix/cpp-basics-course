// TODO (README requirement 5): Why must the InfusionSession be an
// automatic (stack) object, not one created with new?
//
#include "infusion_pump.h"
#include "infusion_session.h"

#include <iostream>
#include <string>
#include <vector>

using makersplace::clinic::InfusionPump;
using makersplace::clinic::InfusionSession;

const double OCCLUSION_LIMIT_MMHG = 300.0;
const double AIR_IN_LINE = -1.0;

// One pressure reading per minute.
void runInfusion(InfusionPump& pump, std::string folder, const std::vector<double>& pressures) {
    std::cout << "Infusion for " << folder << std::endl;
    // TODO: create an InfusionSession (e.g. 100 mL/h), then for each reading:
    //   - reading == AIR_IN_LINE          -> print "AIR IN LINE" and RETURN EARLY
    //   - reading > OCCLUSION_LIMIT_MMHG  -> print "OCCLUSION" and RETURN EARLY
    //   - otherwise session.tick()
    // Finally print "infusion complete".
    (void)pump;
    (void)pressures;
}

int main() {
    InfusionPump pump;
    runInfusion(pump, "CL-0001", {120, 125, 130, 128});
    runInfusion(pump, "CL-0002", {118, 122, 340, 125});
    runInfusion(pump, "CL-0003", {121, AIR_IN_LINE, 119});

    std::cout << "Pump is " << (pump.isRunning() ? "STILL RUNNING (bug!)" : "stopped") << std::endl;
    return 0;
}
