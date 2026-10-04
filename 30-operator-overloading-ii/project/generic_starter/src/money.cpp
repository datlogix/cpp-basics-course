#include "money.h"

#include <cmath>
#include <stdexcept>

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
    // TODO: format as "GHS 1,250.50" (thousands separator, two decimal places,
    // and a minus sign for negative amounts)
    os << "GHS " << m.pesewas / 100.0;
    return os;
}

std::istream& operator>>(std::istream& in, Money& m) {
    // TODO: read a number of cedis; only change m if the read succeeded
    (void)m;
    return in;
}

Money& FeeLedger::operator[](const std::string& studentId) {
    return balances[studentId];
}

const Money& FeeLedger::operator[](const std::string& studentId) const {
    // TODO: throw std::out_of_range for an unknown ID
    return balances.at(studentId);
}

} // namespace makersplace::school
