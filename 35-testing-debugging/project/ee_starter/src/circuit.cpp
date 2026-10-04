#include "circuit.h"

#include <stdexcept>

namespace makersplace::energy {

Circuit::Circuit(std::string n, double breaker) : name(n), breakerAmps(breaker) {
    if (breakerAmps <= 0) {
        throw std::invalid_argument("breaker rating must be positive");
    }
}

void Circuit::addLoad(const std::string& loadName, double watts) {
    if (watts <= 0) {
        throw std::invalid_argument("watts must be positive");
    }
    if (loadWatts.count(loadName) > 0) {
        throw std::invalid_argument("duplicate load " + loadName);
    }
    if (totalAmps() + watts / SUPPLY_VOLTS > breakerAmps) {
        throw std::runtime_error("adding " + loadName + " would trip the breaker");
    }
    loadWatts[loadName] = watts;
}

bool Circuit::removeLoad(const std::string& loadName) {
    return loadWatts.erase(loadName) > 0;
}

double Circuit::totalAmps() const {
    double total = 0;
    for (const auto& entry : loadWatts) {
        total += static_cast<int>(entry.second) / static_cast<int>(SUPPLY_VOLTS);
    }
    return total;
}

} // namespace makersplace::energy
