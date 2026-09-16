// virtual + passing by reference (or pointer) fixes the slicing problem:
// the ACTUAL object type's version runs, not the declared type's.
#include <iostream>
#include <string>

class Component {
protected:
    std::string name;
    double value;
public:
    Component(std::string n, double v) : name(n), value(v) {}
    virtual void describe() {
        std::cout << name << ": " << value << std::endl;
    }
    virtual ~Component() {}
};

class Resistor : public Component {
public:
    Resistor(double ohms) : Component("Resistor", ohms) {}
    void describe() override {
        std::cout << name << ": " << value << " ohms" << std::endl;
    }
};

class Capacitor : public Component {
public:
    Capacitor(double farads) : Component("Capacitor", farads) {}
    void describe() override {
        std::cout << name << ": " << value << " farads" << std::endl;
    }
};

void printIt(Component& c) { // pass BY REFERENCE - no slicing
    c.describe();
}

int main() {
    Resistor r(220.0);
    Capacitor c(0.000001);

    printIt(r); // "Resistor: 220 ohms" - correct now
    printIt(c); // "Capacitor: 1e-06 farads" - correct

    return 0;
}
