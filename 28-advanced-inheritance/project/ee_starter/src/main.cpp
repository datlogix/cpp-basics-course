#include "devices.h"

#include <iostream>
#include <memory>
#include <vector>

using namespace makersplace::energy;

void safetyCheck(PoweredDevice& d) { d.emergencyShutdown(); }
void heartbeat(const NetworkedDevice& d) { d.send("heartbeat"); }

int main() {
    std::vector<std::unique_ptr<Device>> devices;
    devices.push_back(std::make_unique<PoweredDevice>("PD-01", "Kitchen", 230, 1500));
    devices.push_back(std::make_unique<NetworkedDevice>("ND-01", "Lounge", "192.168.1.10", -55));
    // TODO: add a SmartPlug and a SmartMeter

    for (const auto& d : devices) {
        std::cout << "  " << d->describe() << std::endl;
    }

    // TODO (req 2): create a SmartPlug and pass it to BOTH safetyCheck()
    // and heartbeat().
    (void)safetyCheck;
    (void)heartbeat;

    // TODO (req 6): show (in a comment) a line that would slice, and the
    // correct alternative.
    return 0;
}
