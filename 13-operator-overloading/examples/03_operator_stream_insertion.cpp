// Overloading << lets std::cout print your object directly.
// This one must be a free function (a friend), not a class method.
#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r, double i) : real(r), imag(i) {}

    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real << " + " << c.imag << "i";
    return os;
}

int main() {
    Complex c(3, 4);
    std::cout << "c = " << c << std::endl; // "c = 3 + 4i"

    return 0;
}
