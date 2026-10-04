// Object slicing happens whenever a derived object is copied INTO a
// base-class OBJECT: initialisation, assignment, and containers of base
// objects by value. Pointers and references never slice.
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Component {
protected:
    std::string name;
    double value;

public:
    Component(std::string n, double v) : name(n), value(v) {}
    virtual ~Component() {}
    virtual std::string describe() const {
        std::ostringstream out;
        out << name << " " << value;
        return out.str();
    }
};

class Resistor : public Component {
public:
    explicit Resistor(double ohms) : Component("Resistor", ohms) {}
    std::string describe() const override {
        std::ostringstream out;
        out << name << " " << value << " ohms";
        return out.str();
    }
};

int main() {
    Resistor r(220);

    Component c = r;                 // 1. initialising a base object: SLICED
    std::cout << "1. " << c.describe() << std::endl;

    Component c2("Generic", 1);
    c2 = r;                          // 2. assigning to a base object: SLICED
    std::cout << "2. " << c2.describe() << std::endl;

    std::vector<Component> byValue;  // 3. a container of base objects: SLICED
    byValue.push_back(r);
    std::cout << "3. " << byValue[0].describe() << std::endl;

    // Pointers and references never slice:
    const Component& ref = r;
    std::cout << "reference:  " << ref.describe() << std::endl;

    std::vector<std::unique_ptr<Component>> byPointer;
    byPointer.push_back(std::make_unique<Resistor>(220));
    std::cout << "unique_ptr: " << byPointer[0]->describe() << std::endl;
    return 0;
}
