#include "money.h"

#include <cmath>

namespace makersplace::school {

Money Money::fromCedis(double cedis) {
    return Money(std::lround(cedis * 100));
}

Money& Money::operator+=(const Money& other) {
    pesewas += other.pesewas;
    return *this;
}

Money operator+(Money a, const Money& b) {
    return a += b;
}

std::ostream& operator<<(std::ostream& os, const Money& m) {
    long whole = m.pesewas / 100;
    long part = m.pesewas % 100;
    if (part < 0) part = -part;
    os << "GHS " << whole << "." << (part < 10 ? "0" : "") << part;
    return os;
}

} // namespace makersplace::school
