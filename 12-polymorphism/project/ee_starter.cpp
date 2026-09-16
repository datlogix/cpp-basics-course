// Module 12 Project - Track B: Circuit Impedance Calculator
// See project/README.md for requirements.
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

const double PI = 3.14159265358979;

class Component {
protected:
    std::string name;
    double value;

public:
    Component(std::string n, double v) : name(n), value(v) {}
    virtual void describe() {
        std::cout << name << ": " << value << std::endl;
    }
    virtual double impedance(double frequencyHz) {
        return 0;
    }
    virtual ~Component() {}
};

class Resistor : public Component {
public:
    Resistor(double ohms) : Component("Resistor", ohms) {}
    double impedance(double frequencyHz) override {
        return value; // frequency-independent
    }
};

class Capacitor : public Component {
public:
    Capacitor(double farads) : Component("Capacitor", farads) {}
    double impedance(double frequencyHz) override {
        // TODO: 1.0 / (2 * PI * frequencyHz * value)
        return 0;
    }
};

class Inductor : public Component {
public:
    Inductor(double henries) : Component("Inductor", henries) {}
    double impedance(double frequencyHz) override {
        // TODO: 2 * PI * frequencyHz * value
        return 0;
    }
};

int main() {
    const double FREQUENCY_HZ = 60.0;

    std::vector<Component*> circuit;
    circuit.push_back(new Resistor(100.0));
    circuit.push_back(new Capacitor(0.0001));
    circuit.push_back(new Inductor(0.5));

    // TODO: loop over circuit, print each component's impedance(FREQUENCY_HZ),
    // and accumulate a running total.

    // TODO: print the total series impedance.

    // TODO: delete every pointer in circuit.

    return 0;
}
