// Overloading == lets two custom objects be compared with natural syntax.
#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r, double i) : real(r), imag(i) {}

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    double getReal() const { return real; }
    double getImag() const { return imag; }
};

int main() {
    Complex a(3, 4);
    Complex b(3, 4);
    Complex c(1, 1);

    std::cout << "a == b: " << (a == b) << std::endl; // 1 (true)
    std::cout << "a == c: " << (a == c) << std::endl; // 0 (false)

    return 0;
}
