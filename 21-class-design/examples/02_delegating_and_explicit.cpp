// Delegating constructors keep validation in ONE place.
// explicit stops a single-argument constructor from silently
// converting a double into a Resistor.
#include <iostream>

class Resistor {
private:
    double ohms;
    double tolerancePercent;

public:
    // The main constructor: all validation lives here, once.
    Resistor(double r, double tol) : ohms(r), tolerancePercent(tol) {
        if (ohms <= 0) {
            std::cout << "  (invalid resistance " << r << ", using 1 ohm)" << std::endl;
            ohms = 1.0;
        }
        if (tolerancePercent <= 0) {
            tolerancePercent = 5.0;
        }
    }

    // Delegating constructor: "no tolerance given" means 5%.
    explicit Resistor(double r) : Resistor(r, 5.0) {}

    double getOhms() const { return ohms; }
    double getTolerance() const { return tolerancePercent; }
};

void printResistor(const Resistor& r) {
    std::cout << r.getOhms() << " ohms +/- " << r.getTolerance() << "%" << std::endl;
}

int main() {
    Resistor a(220.0, 1.0);
    Resistor b(4700.0);   // delegates to Resistor(4700.0, 5.0)
    Resistor c(-10.0);    // validation still runs, via the main constructor

    printResistor(a);
    printResistor(b);
    printResistor(c);

    // printResistor(330.0);        // ERROR with explicit: no silent conversion
    printResistor(Resistor(330.0)); // OK: the caller says what they mean

    return 0;
}
