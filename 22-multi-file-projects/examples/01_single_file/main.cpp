// The starting point: one class and main() all in ONE file.
// 02_header_and_source/ splits exactly this program into three files.
//
// Build and run (from inside this folder):
//   g++ -std=c++17 -Wall -Wextra main.cpp -o geometry
//   ./geometry
#include <cmath>
#include <iostream>

class Point {
private:
    double x;
    double y;

public:
    Point(double xValue, double yValue) : x(xValue), y(yValue) {}

    double distanceTo(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ")";
    }
};

int main() {
    Point a(0, 0);
    Point b(3, 4);

    a.print();
    std::cout << " to ";
    b.print();
    std::cout << " is " << a.distanceTo(b) << " units" << std::endl;
    return 0;
}
