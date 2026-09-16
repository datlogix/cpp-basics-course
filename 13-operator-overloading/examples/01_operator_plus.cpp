// Overloading + lets two custom objects be combined with natural syntax.
#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    double getReal() const { return real; }
    double getImag() const { return imag; }
};

int main() {
    Complex a(3, 4);
    Complex b(1, 2);
    Complex c = a + b; // calls a.operator+(b)

    std::cout << c.getReal() << " + " << c.getImag() << "i" << std::endl;

    return 0;
}
