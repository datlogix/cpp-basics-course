// Copying polymorphic objects without knowing their type: a virtual
// clone(). Plus a covariant return type on a raw-pointer version.
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    virtual std::string describe() const = 0;
    virtual void scale(double factor) = 0;
    virtual std::unique_ptr<Shape> clone() const = 0; // "copy yourself, whatever you are"

    // A raw-pointer version, only to demonstrate COVARIANT return types.
    // (The caller must delete the result - prefer clone() in real code.)
    virtual Shape* cloneRaw() const = 0;
};

class Circle : public Shape {
private:
    double radius;

public:
    explicit Circle(double r) : radius(r) {}
    std::string describe() const override { return "Circle r=" + std::to_string(radius).substr(0, 4); }
    void scale(double factor) override { radius *= factor; }
    std::unique_ptr<Shape> clone() const override { return std::make_unique<Circle>(*this); }

    // Covariant return type: the base returns Shape*, but this override is
    // allowed to return the MORE DERIVED Circle*.
    Circle* cloneRaw() const override { return new Circle(*this); }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}
    std::string describe() const override {
        return "Rectangle " + std::to_string(width).substr(0, 4) + "x" + std::to_string(height).substr(0, 4);
    }
    void scale(double factor) override {
        width *= factor;
        height *= factor;
    }
    std::unique_ptr<Shape> clone() const override { return std::make_unique<Rectangle>(*this); }
    Rectangle* cloneRaw() const override { return new Rectangle(*this); } // covariant too
};

void print(const std::string& title, const std::vector<std::unique_ptr<Shape>>& shapes) {
    std::cout << title << std::endl;
    for (const auto& s : shapes) {
        std::cout << "  " << s->describe() << std::endl;
    }
}

int main() {
    std::vector<std::unique_ptr<Shape>> original;
    original.push_back(std::make_unique<Circle>(1.0));
    original.push_back(std::make_unique<Rectangle>(2.0, 3.0));

    // Deep-copy the whole collection, each object copied as its REAL type.
    std::vector<std::unique_ptr<Shape>> copy;
    for (const auto& s : original) {
        copy.push_back(s->clone());
    }

    for (const auto& s : copy) {
        s->scale(2.0); // change only the copies
    }

    print("Original:", original);
    print("Scaled copy:", copy);

    Circle c(5.0);
    // Covariant: called on a Circle, cloneRaw() gives a Circle* - no cast needed.
    // We hand it straight to a unique_ptr so it is deleted automatically.
    std::unique_ptr<Circle> raw(c.cloneRaw());
    std::cout << "Raw clone: " << raw->describe() << std::endl;
    return 0;
}
