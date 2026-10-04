// Static binding (decided at compile time by the DECLARED type) vs
// dynamic binding (decided at runtime by the ACTUAL type, via the vtable).
#include <iostream>
#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual std::string name() const { return "Shape"; } // virtual: dynamic binding
    std::string category() const { return "a shape"; }   // NOT virtual: static binding
};

class Circle : public Shape {
public:
    std::string name() const override { return "Circle"; }
    std::string category() const { return "a round shape"; } // hides, doesn't override
};

// Two classes with the same data: one with virtual functions, one without.
class PlainPoint {
    double x = 0, y = 0;

public:
    double sum() const { return x + y; }
};

class PolymorphicPoint {
    double x = 0, y = 0;

public:
    virtual ~PolymorphicPoint() = default;
    virtual double sum() const { return x + y; }
};

int main() {
    Circle c;
    Shape& s = c;

    std::cout << "Through a Shape& referring to a Circle:" << std::endl;
    std::cout << "  s.name()     = " << s.name() << "   (virtual -> dynamic -> Circle's)" << std::endl;
    std::cout << "  s.category() = " << s.category() << "  (non-virtual -> static -> Shape's)"
              << std::endl;

    std::cout << "Directly on the Circle object:" << std::endl;
    std::cout << "  c.category() = " << c.category() << std::endl;

    std::cout << "The hidden vtable pointer makes polymorphic objects bigger:" << std::endl;
    std::cout << "  sizeof(PlainPoint)       = " << sizeof(PlainPoint) << " bytes" << std::endl;
    std::cout << "  sizeof(PolymorphicPoint) = " << sizeof(PolymorphicPoint) << " bytes" << std::endl;
    return 0;
}
