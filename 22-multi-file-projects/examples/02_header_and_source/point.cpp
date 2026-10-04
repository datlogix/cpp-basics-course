// point.cpp - the SOURCE file: HOW a Point does it (definitions).
#include "point.h" // always include your own header first

#include <cmath>
#include <iostream>

Point::Point(double xValue, double yValue) : x(xValue), y(yValue) {}

double Point::distanceTo(const Point& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

void Point::print() const {
    std::cout << "(" << x << ", " << y << ")";
}
