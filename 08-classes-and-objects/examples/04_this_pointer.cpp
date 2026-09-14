// this-> is needed when a parameter name shadows a member variable name.
#include <iostream>

class Point {
private:
    int x, y;

public:
    Point(int x, int y) {
        this->x = x;  // "this object's x" = the parameter named x
        this->y = y;
    }

    void print() {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    Point p(3, 4);
    p.print(); // (3, 4)
    return 0;
}
