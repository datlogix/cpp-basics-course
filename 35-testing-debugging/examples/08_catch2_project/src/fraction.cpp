#include "fraction.h"

#include <numeric>
#include <stdexcept>

Fraction::Fraction(long n, long d) : num(n), den(d) {
    if (den == 0) {
        throw std::invalid_argument("denominator cannot be zero");
    }
    reduce();
}

void Fraction::reduce() {
    if (den < 0) {
        num = -num;
        den = -den;
    }
    long g = std::gcd(num, den);
    if (g != 0) {
        num /= g;
        den /= g;
    }
}

Fraction& Fraction::operator+=(const Fraction& o) {
    num = num * o.den + o.num * den;
    den = den * o.den;
    reduce();
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& o) {
    num *= o.num;
    den *= o.den;
    reduce();
    return *this;
}

Fraction operator+(Fraction a, const Fraction& b) { return a += b; }
Fraction operator*(Fraction a, const Fraction& b) { return a *= b; }

std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    os << f.num;
    if (f.den != 1) {
        os << "/" << f.den;
    }
    return os;
}
