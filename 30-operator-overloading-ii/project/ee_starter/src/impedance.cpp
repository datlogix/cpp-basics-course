#include "impedance.h"

#include <cmath>
#include <stdexcept>

namespace makersplace::energy {

double Impedance::magnitude() const {
    // TODO
    return 0;
}

double Impedance::phaseDegrees() const {
    // TODO
    return 0;
}

Impedance& Impedance::operator+=(const Impedance& o) {
    r += o.r;
    x += o.x;
    return *this;
}

Impedance operator+(Impedance a, const Impedance& b) {
    return a += b;
}

Impedance parallel(const Impedance& a, const Impedance& b) {
    // TODO: (a * b) / (a + b)
    (void)a;
    (void)b;
    return Impedance();
}

std::ostream& operator<<(std::ostream& os, const Impedance& z) {
    os << z.r << (z.x < 0 ? " - j" : " + j") << std::fabs(z.x) << " ohm";
    return os;
}

std::istream& operator>>(std::istream& in, Impedance& z) {
    // TODO: read R then X; only change z if both reads succeed
    (void)z;
    return in;
}

ComponentSpec& Network::operator[](const std::string& designator) {
    return parts[designator];
}

const ComponentSpec& Network::operator[](const std::string& designator) const {
    // TODO: throw std::out_of_range with a helpful message for unknown designators
    return parts.at(designator);
}

} // namespace makersplace::energy
