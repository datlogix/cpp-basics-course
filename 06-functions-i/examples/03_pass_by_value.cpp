// By default, arguments are COPIED into a function's parameters.
// Changing the parameter never affects the caller's original variable.
#include <iostream>

void tryToDouble(int x) {
    x = x * 2;
    std::cout << "Inside tryToDouble, x is now: " << x << std::endl;
}

int main() {
    int number = 5;
    tryToDouble(number);
    std::cout << "Back in main, number is still: " << number << std::endl; // still 5
    return 0;
}
