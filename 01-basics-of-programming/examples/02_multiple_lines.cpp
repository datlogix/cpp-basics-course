// Every std::cout is its own statement; endl moves to a new line.
// You can also print several things in one statement by chaining <<.
#include <iostream>

int main() {
    std::cout << "Line one" << std::endl;
    std::cout << "Line two" << std::endl;

    std::cout << "Chained: " << "part A, " << "part B" << std::endl;

    return 0;
}
