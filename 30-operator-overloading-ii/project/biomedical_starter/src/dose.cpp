#include "dose.h"

#include <cmath>
#include <stdexcept>

namespace makersplace::clinic {

Dose Dose::mg(double milligrams) {
    Dose d;
    d.micrograms = std::lround(milligrams * 1000);
    return d;
}

Dose Dose::mcg(long mcg) {
    Dose d;
    d.micrograms = mcg;
    return d;
}

Dose& Dose::operator+=(const Dose& other) {
    micrograms += other.micrograms;
    return *this;
}

Dose operator+(Dose a, const Dose& b) {
    return a += b;
}

std::ostream& operator<<(std::ostream& os, const Dose& d) {
    if (d.micrograms % 1000 == 0) {
        os << d.micrograms / 1000 << " mg";
    } else {
        os << d.micrograms << " mcg";
    }
    return os;
}

std::istream& operator>>(std::istream& in, Dose& d) {
    // TODO: read a number and a unit ("mg" or "mcg"); reject anything else with
    // in.setstate(std::ios::failbit) and leave d unchanged
    (void)d;
    return in;
}

Dose& MedicationChart::operator[](int hour) {
    // TODO: throw std::out_of_range outside 0..23
    return hourly[hour];
}

const Dose& MedicationChart::operator[](int hour) const {
    // TODO: throw std::out_of_range outside 0..23
    return hourly[hour];
}

Dose MedicationChart::dailyTotal() const {
    // TODO
    return Dose();
}

} // namespace makersplace::clinic
