// using Base::Base; gives a derived class all of the base's constructors,
// so it doesn't have to forward each one by hand.
#include <iostream>
#include <string>

class Component {
protected:
    std::string label;
    double value;

public:
    Component(std::string l, double v) : label(l), value(v) {}
    explicit Component(std::string l) : Component(l, 0.0) {}
    virtual ~Component() {}
    std::string getLabel() const { return label; }
};

// Without inheriting constructors: forwarding by hand.
class FuseManual : public Component {
public:
    FuseManual(std::string l, double amps) : Component(l, amps) {}
    explicit FuseManual(std::string l) : Component(l) {}
    bool blowsAt(double amps) const { return amps > value; }
};

// With inheriting constructors: one line.
class Fuse : public Component {
private:
    bool blown = false; // a new member is fine IF it has a default member initializer

public:
    using Component::Component; // Fuse(std::string, double) and Fuse(std::string)

    bool test(double amps) {
        if (amps > value) {
            blown = true;
        }
        return !blown;
    }
    bool isBlown() const { return blown; }
};

int main() {
    FuseManual old("F0", 5.0);
    std::cout << old.getLabel() << " blows at 6 A? " << (old.blowsAt(6.0) ? "yes" : "no") << std::endl;

    Fuse f1("F1", 13.0);
    Fuse f2("F2"); // the single-argument constructor was inherited too

    f1.test(10.0);
    std::cout << f1.getLabel() << " after 10 A: " << (f1.isBlown() ? "blown" : "ok") << std::endl;
    f1.test(20.0);
    std::cout << f1.getLabel() << " after 20 A: " << (f1.isBlown() ? "blown" : "ok") << std::endl;
    std::cout << f2.getLabel() << " has rating 0 A, so any current blows it: "
              << (f2.test(0.1) ? "ok" : "blown") << std::endl;
    return 0;
}
