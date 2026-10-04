#pragma once

#include <compare>
#include <iostream>

// A Fraction always stored in lowest terms with a positive denominator
// (Module 30's exercise, now with a test suite).
class Fraction {
private:
    long num;
    long den;
    void reduce();

public:
    Fraction(long n = 0, long d = 1); // throws std::invalid_argument if d == 0

    long numerator() const { return num; }
    long denominator() const { return den; }

    Fraction& operator+=(const Fraction& o);
    Fraction& operator*=(const Fraction& o);

    std::strong_ordering operator<=>(const Fraction& o) const { return num * o.den <=> o.num * den; }
    bool operator==(const Fraction& o) const { return num == o.num && den == o.den; }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
};

Fraction operator+(Fraction a, const Fraction& b);
Fraction operator*(Fraction a, const Fraction& b);
