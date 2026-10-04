// Liskov Substitution Principle: a derived class must work correctly
// wherever its base is expected. Square-derived-from-Rectangle breaks it.
#include <iostream>
#include <memory>
#include <vector>

namespace before {

class Rectangle {
protected:
    double width = 0, height = 0;

public:
    virtual ~Rectangle() = default;
    virtual void setWidth(double w) { width = w; }
    virtual void setHeight(double h) { height = h; }
    double area() const { return width * height; }
};

class Square : public Rectangle {
public:
    void setWidth(double w) override { width = height = w; }
    void setHeight(double h) override { width = height = h; }
};

// Written for Rectangles. Its assumption: setting the height leaves the width alone.
void resizeBillboard(Rectangle& r) {
    r.setWidth(4);
    r.setHeight(5);
    std::cout << "  expected area 20, got " << r.area()
              << (r.area() == 20 ? "" : "   <- LSP violated!") << std::endl;
}

} // namespace before

namespace after {

// Shapes are immutable here: no setters for a subclass to break.
// Each shape is constructed with exactly the data it needs.
class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override { return width * height; }
};

class Square : public Shape {
    double side;
public:
    explicit Square(double s) : side(s) {}
    double area() const override { return side * side; }
};

double totalArea(const std::vector<std::unique_ptr<Shape>>& shapes) {
    double total = 0;
    for (const auto& s : shapes) total += s->area(); // correct for EVERY Shape
    return total;
}

} // namespace after

int main() {
    std::cout << "before:" << std::endl;
    before::Rectangle r;
    before::Square s;
    before::resizeBillboard(r);
    before::resizeBillboard(s);

    std::cout << "after:" << std::endl;
    std::vector<std::unique_ptr<after::Shape>> shapes;
    shapes.push_back(std::make_unique<after::Rectangle>(4, 5));
    shapes.push_back(std::make_unique<after::Square>(5));
    std::cout << "  total area " << after::totalArea(shapes) << std::endl;
    return 0;
}
