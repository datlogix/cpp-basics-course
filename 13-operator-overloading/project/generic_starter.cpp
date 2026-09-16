// Module 13 Project - Track A: Vector2D
// See project/README.md for requirements.
#include <iostream>

class Vector2D {
private:
    double x, y;

public:
    Vector2D(double x, double y) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& other) const {
        // TODO: component-wise addition
        return Vector2D(0, 0);
    }

    bool operator==(const Vector2D& other) const {
        // TODO: both components equal
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);
};

std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    // TODO: print "(x, y)"
    return os;
}

int main() {
    Vector2D a(1.0, 2.0);
    Vector2D b(3.0, 4.0);

    // TODO: print a + b, and check whether a == b.

    return 0;
}
