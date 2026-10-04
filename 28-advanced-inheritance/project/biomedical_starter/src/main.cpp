#include "devices.h"

#include <iostream>
#include <memory>
#include <vector>

using namespace makersplace::clinic;

void chargingRound(const Wearable& w) {
    std::cout << "  " << w.getSerial() << (w.needsCharging() ? " needs charging" : " is fine") << std::endl;
}
void pairingCheck(const WirelessDevice& d) { d.transmit("pairing check"); }

int main() {
    std::vector<std::unique_ptr<MedicalDevice>> devices;
    devices.push_back(std::make_unique<Wearable>("WR-01", "CL-0001", 15));
    devices.push_back(std::make_unique<WirelessDevice>("WD-01", "CL-0002", "BT:4F:21"));
    // TODO: add a SmartWatchMonitor and a WirelessEcgPatch

    for (const auto& d : devices) {
        std::cout << "  " << d->status() << std::endl;
    }

    // TODO (req 2): create a SmartWatchMonitor and pass it to BOTH
    // chargingRound() and pairingCheck().
    (void)chargingRound;
    (void)pairingCheck;

    // TODO (req 6): show (in a comment) a line that would slice, and the
    // correct alternative.
    return 0;
}
