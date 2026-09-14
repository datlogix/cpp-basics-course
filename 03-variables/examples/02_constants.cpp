// const locks a value in. Uncomment the last line to see the compiler
// refuse to build the program - that's const doing its job.
#include <iostream>

int main() {
    const double PI = 3.14159;
    double radius = 4.0;
    double area = PI * radius * radius;

    std::cout << "Area: " << area << std::endl;

    // PI = 4;   // <- uncomment this line: compiler error, on purpose.

    return 0;
}
