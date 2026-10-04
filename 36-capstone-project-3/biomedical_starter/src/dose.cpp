#include "dose.h"

#include <cmath>

namespace makersplace::clinic {

Dose Dose::mg(double milligrams) {
    Dose d;
    d.micrograms = std::lround(milligrams * 1000);
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

} // namespace makersplace::clinic
