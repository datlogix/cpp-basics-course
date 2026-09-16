// Module 11 Project - Track B: Circuit Component Hierarchy
// See project/README.md for requirements.
#include <iostream>
#include <string>

class Component {
protected:
    std::string name;
    double value;

public:
    Component(std::string n, double v) : name(n), value(v) {}

    void describe() {
        std::cout << name << ": " << value << std::endl;
    }
};

class Resistor : public Component {
public:
    Resistor(double ohms) : Component("Resistor", ohms) {}

    // TODO: override describe() to print the value with unit "ohms"
};

class Capacitor : public Component {
public:
    Capacitor(double farads) : Component("Capacitor", farads) {}

    // TODO: override describe() to print the value with unit "farads"
};

class Inductor : public Component {
public:
    Inductor(double henries) : Component("Inductor", henries) {}

    // TODO: override describe() to print the value with unit "henries"
};

int main() {
    Resistor r(220.0);
    Capacitor c(0.000001);
    Inductor l(0.05);

    r.describe();
    c.describe();
    l.describe();

    return 0;
}
