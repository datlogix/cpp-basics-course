#include <iostream>

class Rectangle {
private:
    double length;
    double width;

public:
    Rectangle(double length, double width) {
        this->length = length;
        this->width = width;
    }

    double area() {
        return length * width;
    }

    double perimeter() {
        return 2 * (length + width);
    }

    void scale(double factor) {
        length *= factor;
        width *= factor;
    }
};

int main() {
    Rectangle r1(4.0, 5.0);
    Rectangle r2(2.0, 3.0);

    std::cout << "r1 area: " << r1.area() << " perimeter: " << r1.perimeter() << std::endl;
    std::cout << "r2 area: " << r2.area() << " perimeter: " << r2.perimeter() << std::endl;

    r1.scale(2.0);
    std::cout << "r1 area after scaling: " << r1.area() << std::endl;

    return 0;
}
