#include "fraction.h"

#include <iostream>

int main() {
    Fraction half(1, 2);
    Fraction third(1, 3);
    std::cout << half << " + " << third << " = " << half + third << std::endl;
    std::cout << half << " * " << third << " = " << half * third << std::endl;
    return 0;
}
