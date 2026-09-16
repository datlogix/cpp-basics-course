// Module 13 Project - Track B: Complex Impedance
// See project/README.md for requirements.
#include <iostream>

class Complex {
private:
    double real, imag;

public:
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex& other) const {
        // TODO
        return Complex(0, 0);
    }

    Complex operator-(const Complex& other) const {
        // TODO
        return Complex(0, 0);
    }

    Complex operator*(const Complex& other) const {
        // TODO: (a+bi)(c+di) = (ac - bd) + (ad + bc)i
        return Complex(0, 0);
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    // TODO: print "a + bi"
    return os;
}

int main() {
    Complex resistorImpedance(50.0, 0.0);   // 50 ohms, purely resistive
    Complex capacitorImpedance(0.0, -30.0); // -j30 ohms, purely reactive

    // TODO: compute and print the series total: Ztotal = Z1 + Z2

    return 0;
}
