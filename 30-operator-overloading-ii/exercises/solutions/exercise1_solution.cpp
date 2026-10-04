#include <algorithm>
#include <compare>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

class Fraction {
private:
    long num;
    long den;

    void reduce() {
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

public:
    Fraction(long n = 0, long d = 1) : num(n), den(d == 0 ? 1 : d) { reduce(); }

    long numerator() const { return num; }
    long denominator() const { return den; }

    // TODO 1
    Fraction& operator+=(const Fraction& o) {
        num = num * o.den + o.num * den;
        den = den * o.den;
        reduce();
        return *this;
    }
    Fraction& operator-=(const Fraction& o) {
        num = num * o.den - o.num * den;
        den = den * o.den;
        reduce();
        return *this;
    }
    Fraction& operator*=(const Fraction& o) {
        num *= o.num;
        den *= o.den;
        reduce();
        return *this;
    }

    // TODO 3
    Fraction& operator++() {
        num += den;
        return *this; // adding den/den keeps lowest terms
    }
    Fraction operator++(int) {
        Fraction old = *this;
        ++(*this);
        return old;
    }

    // TODO 4
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        os << f.num;
        if (f.den != 1) {
            os << "/" << f.den;
        }
        return os;
    }

    // TODO 5
    friend std::istream& operator>>(std::istream& in, Fraction& f) {
        long n, d;
        char slash;
        if (in >> n >> slash >> d) {
            if (slash == '/' && d != 0) {
                f = Fraction(n, d);
            } else {
                in.setstate(std::ios::failbit);
            }
        }
        return in;
    }

    // TODO 6
    explicit operator double() const { return static_cast<double>(num) / den; }

    // TODO 7
    std::strong_ordering operator<=>(const Fraction& o) const { return num * o.den <=> o.num * den; }
    bool operator==(const Fraction& o) const { return num == o.num && den == o.den; }
};

// TODO 2 - an int converts to a Fraction through the (non-explicit)
// constructor, so these also give us Fraction * int and int * Fraction.
Fraction operator+(Fraction a, const Fraction& b) { return a += b; }
Fraction operator-(Fraction a, const Fraction& b) { return a -= b; }
Fraction operator*(Fraction a, const Fraction& b) { return a *= b; }

int main() {
    Fraction half(1, 2), third(1, 3);
    std::cout << half << " + " << third << " = " << half + third << std::endl;
    std::cout << half << " - " << third << " = " << half - third << std::endl;
    std::cout << "3 * 1/3 = " << 3 * third << ", 1/3 * 3 = " << third * 3 << std::endl;

    Fraction f(3, 4);
    std::cout << "f++ gives " << f++ << ", then f is " << f << std::endl;
    std::cout << "++f gives " << ++f << std::endl;
    std::cout << "as decimal: " << static_cast<double>(f) << std::endl;

    std::istringstream input("2/6 5/0 7/8");
    Fraction a, b(9, 9);
    input >> a;
    std::cout << "read " << a << std::endl;
    if (!(input >> b)) {
        std::cout << "5/0 rejected, b is still " << b << std::endl;
    }

    std::vector<Fraction> v = {Fraction(3, 4), Fraction(1, 2), Fraction(5, 6), Fraction(2, 4)};
    std::sort(v.begin(), v.end());
    for (const Fraction& x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl << "1/2 == 2/4 ? " << (Fraction(1, 2) == Fraction(2, 4)) << std::endl;
    return 0;
}
