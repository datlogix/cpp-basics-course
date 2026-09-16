// Module 11 Project - Track A: Shape Hierarchy
// See project/README.md for requirements.
#include <iostream>
#include <string>

class Shape {
protected:
    std::string name;

public:
    Shape(std::string n) : name(n) {}
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : Shape("Circle"), radius(r) {}

    double area() {
        // TODO: pi * radius * radius
        return 0;
    }
};

class Rectangle : public Shape {
private:
    double length;
    double width;

public:
    Rectangle(double l, double w) : Shape("Rectangle"), length(l), width(w) {}

    double area() {
        // TODO: length * width
        return 0;
    }
};

int main() {
    Circle c(4.0);
    Rectangle r(3.0, 5.0);

    // TODO: print "<name>: area = <area>" for both.
    // Shape's name is protected, so a public getter or friend access
    // would be needed to read it from main - simplest fix: add a
    // public std::string getName() to Shape.

    return 0;
}
