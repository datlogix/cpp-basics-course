#include "energy.h"

#include <cmath>

namespace makersplace::energy {

Energy Energy::fromKwh(double kwh) {
    Energy e;
    e.wattHours = std::lround(kwh * 1000);
    return e;
}

Energy Energy::fromPower(double watts, double hours) {
    Energy e;
    e.wattHours = std::lround(watts * hours);
    return e;
}

Energy& Energy::operator+=(const Energy& other) {
    wattHours += other.wattHours;
    return *this;
}

Energy operator+(Energy a, const Energy& b) {
    return a += b;
}

std::ostream& operator<<(std::ostream& os, const Energy& e) {
    os << e.kwh() << " kWh";
    return os;
}

} // namespace makersplace::energy
