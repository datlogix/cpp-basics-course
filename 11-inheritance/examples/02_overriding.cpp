// A derived class can redefine a method it inherited. Called through a
// variable of the derived type, its own version runs.
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

int main() {
    Component generic("Generic part", 1.0);
    generic.describe();

    Resistor r(220.0);
    r.describe(); // Resistor's own version runs

    return 0;
}
