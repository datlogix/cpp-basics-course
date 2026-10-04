#pragma once

#include "infusion_pump.h"

#include <string>

namespace makersplace::clinic {

// RAII: constructing an InfusionSession STARTS the pump; destroying it
// STOPS the pump - on every exit path.
class InfusionSession {
private:
    InfusionPump& pump;
    std::string folderNumber;
    int minutesRun = 0;

public:
    InfusionSession(InfusionPump& p, std::string folder, double rateMlPerHour);
    ~InfusionSession();

    void tick() { minutesRun++; } // call once per simulated minute
};

} // namespace makersplace::clinic
