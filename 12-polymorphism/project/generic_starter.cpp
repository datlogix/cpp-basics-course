// Module 12 Project - Track A: Shape Collection
// See project/README.md for requirements.
#include <iostream>
#include <string>
#include <vector>

class Shape {
protected:
    std::string name;

public:
    Shape(std::string n) : name(n) {}
    virtual double area() { return 0; }
    virtual ~Shape() {}
    std::string getName() { return name; }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : Shape("Circle"), radius(r) {}
    double area() override {
        // TODO: pi * radius * radius
        return 0;
    }
};

class Rectangle : public Shape {
private:
    double length, width;

public:
    Rectangle(double l, double w) : Shape("Rectangle"), length(l), width(w) {}
    double area() override {
        // TODO: length * width
        return 0;
    }
};

int main() {
    std::vector<Shape*> shapes;
    shapes.push_back(new Circle(4.0));
    shapes.push_back(new Rectangle(3.0, 5.0));

    // TODO: loop over shapes, print each name + area, and accumulate a total.

    // TODO: print the total area.

    // TODO: delete every pointer in shapes.

    return 0;
}
