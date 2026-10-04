// dynamic_cast and typeid (RTTI) - and the virtual-function design that
// usually makes them unnecessary.
#include <iostream>
#include <memory>
#include <typeinfo>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

class Circle : public Shape {
public:
    double radius;
    explicit Circle(double r) : radius(r) {}
    double area() const override { return 3.14159 * radius * radius; }
};

class Square : public Shape {
public:
    double side;
    explicit Square(double s) : side(s) {}
    double area() const override { return side * side; }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(1.0));
    shapes.push_back(std::make_unique<Square>(2.0));
    shapes.push_back(std::make_unique<Circle>(3.0));

    std::cout << "dynamic_cast with pointers (nullptr if it isn't one):" << std::endl;
    for (const auto& s : shapes) {
        if (const Circle* c = dynamic_cast<const Circle*>(s.get())) {
            std::cout << "  a circle of radius " << c->radius << std::endl;
        } else {
            std::cout << "  not a circle" << std::endl;
        }
    }

    std::cout << "dynamic_cast with a reference (throws if it isn't one):" << std::endl;
    try {
        const Circle& c = dynamic_cast<const Circle&>(*shapes[1]);
        std::cout << "  radius " << c.radius << std::endl;
    } catch (const std::bad_cast& e) {
        std::cout << "  std::bad_cast: shapes[1] is not a Circle" << std::endl;
    }

    std::cout << "typeid:" << std::endl;
    for (const auto& s : shapes) {
        std::cout << "  " << (typeid(*s) == typeid(Square) ? "Square" : "not a Square") << std::endl;
    }

    // The SMELL: choosing behaviour by checking types...
    double smellyTotal = 0;
    for (const auto& s : shapes) {
        if (auto c = dynamic_cast<const Circle*>(s.get())) {
            smellyTotal += 3.14159 * c->radius * c->radius;
        } else if (auto q = dynamic_cast<const Square*>(s.get())) {
            smellyTotal += q->side * q->side;
        } // a new Triangle would silently be left out!
    }

    // ...vs the polymorphic design: one virtual call, works for every future shape.
    double total = 0;
    for (const auto& s : shapes) {
        total += s->area();
    }
    std::cout << "Total area: " << smellyTotal << " (type checks) vs " << total << " (virtual)"
              << std::endl;
    return 0;
}
