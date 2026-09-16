// Without virtual, calling through a base-class parameter/pointer runs
// the BASE class's version, even if the object is really a derived type.
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
    void describe() {
        std::cout << name << ": " << value << " ohms" << std::endl;
    }
};

void printIt(Component c) { // pass BY VALUE - this slices
    c.describe();
}

int main() {
    Resistor r(220.0);
    r.describe();   // "Resistor: 220 ohms" - correct
    printIt(r);      // "Resistor: 220" - wrong unit, sliced to Component

    return 0;
}
