// The real payoff: a vector of base-class pointers holding mixed
// derived types, all handled correctly by one loop.
#include <iostream>
#include <string>
#include <vector>

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

class Inductor : public Component {
public:
    Inductor(double henries) : Component("Inductor", henries) {}
    void describe() override {
        std::cout << name << ": " << value << " henries" << std::endl;
    }
};

int main() {
    std::vector<Component*> circuit;
    circuit.push_back(new Resistor(220.0));
    circuit.push_back(new Capacitor(0.000001));
    circuit.push_back(new Inductor(0.05));

    for (Component* c : circuit) {
        c->describe(); // correctly calls EACH object's own version
    }

    for (Component* c : circuit) {
        delete c; // virtual ~Component() makes this safe and correct
    }

    return 0;
}
