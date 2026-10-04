// Module 12's polymorphic circuit, rewritten with unique_ptr:
// virtual dispatch works exactly the same, and there is no delete loop.
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Component {
protected:
    std::string name;
    double value;

public:
    Component(std::string n, double v) : name(n), value(v) {}
    virtual ~Component() { std::cout << "  [-] " << name << std::endl; } // still required!
    virtual void describe() const { std::cout << name << ": " << value << std::endl; }
};

class Resistor : public Component {
public:
    explicit Resistor(double ohms) : Component("Resistor", ohms) {}
    void describe() const override { std::cout << name << ": " << value << " ohms" << std::endl; }
};

class Capacitor : public Component {
public:
    explicit Capacitor(double farads) : Component("Capacitor", farads) {}
    void describe() const override { std::cout << name << ": " << value << " farads" << std::endl; }
};

class Inductor : public Component {
public:
    explicit Inductor(double henries) : Component("Inductor", henries) {}
    void describe() const override { std::cout << name << ": " << value << " henries" << std::endl; }
};

int main() {
    std::vector<std::unique_ptr<Component>> circuit;
    circuit.push_back(std::make_unique<Resistor>(220.0));   // unique_ptr<Resistor> converts
    circuit.push_back(std::make_unique<Capacitor>(0.000001)); // to unique_ptr<Component>
    circuit.push_back(std::make_unique<Inductor>(0.05));

    for (const std::unique_ptr<Component>& c : circuit) { // by reference - no copies
        c->describe();
    }

    // The same loop with auto - the compiler works out the long type:
    for (const auto& c : circuit) {
        c->describe();
    }

    std::cout << "end of main - no delete loop needed:" << std::endl;
    return 0;
}
