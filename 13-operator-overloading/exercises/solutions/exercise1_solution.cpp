#include <iostream>

class Fraction {
private:
    int numerator;
    int denominator;

public:
    Fraction(int n, int d) : numerator(n), denominator(d) {}

    Fraction operator+(const Fraction& other) const {
        int newNum = numerator * other.denominator + other.numerator * denominator;
        int newDen = denominator * other.denominator;
        return Fraction(newNum, newDen);
    }

    bool operator==(const Fraction& other) const {
        return numerator * other.denominator == other.numerator * denominator;
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
};

std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    os << f.numerator << "/" << f.denominator;
    return os;
}

int main() {
    Fraction a(1, 2);
    Fraction b(1, 3);

    Fraction sum = a + b;
    std::cout << a << " + " << b << " = " << sum << std::endl;

    Fraction c(2, 4);
    std::cout << "a == c: " << (a == c) << std::endl; // 1/2 == 2/4 -> true

    return 0;
}
