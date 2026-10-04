// += does the real work as a member; + is a non-member built on it.
// A non-member * makes 2.0 * v work as well as v * 2.0 (symmetry).
#include <iostream>

class Vector2D {
private:
    double x, y;

public:
    Vector2D(double xv, double yv) : x(xv), y(yv) {}

    // Compound assignment: modify *this, return it by reference.
    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vector2D& operator-=(const Vector2D& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vector2D& operator*=(double k) {
        x *= k;
        y *= k;
        return *this;
    }

    // A friend function can also be DEFINED right here inside the class.
    // It is still a non-member function, not a method.
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

// Binary operators as NON-members, written in terms of the compound ones.
Vector2D operator+(Vector2D left, const Vector2D& right) { return left += right; }
Vector2D operator-(Vector2D left, const Vector2D& right) { return left -= right; }
Vector2D operator*(Vector2D v, double k) { return v *= k; }
Vector2D operator*(double k, Vector2D v) { return v *= k; } // the symmetric version

int main() {
    Vector2D position(0, 0);
    Vector2D velocity(1.5, 0.5); // a robot moving across the lab floor, metres per second

    for (int second = 1; second <= 3; second++) {
        position += velocity;
        std::cout << "after " << second << " s: " << position << std::endl;
    }

    Vector2D target(10, 2);
    std::cout << "distance still to go: " << target - position << std::endl;
    std::cout << "velocity * 2 = " << velocity * 2.0 << std::endl;
    std::cout << "2 * velocity = " << 2.0 * velocity << std::endl;

    Vector2D a(1, 1);
    (a += Vector2D(1, 0)) += Vector2D(0, 1); // chaining works because += returns a reference
    std::cout << "chained: " << a << std::endl;
    return 0;
}
