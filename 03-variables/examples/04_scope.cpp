// A variable declared inside { } does not exist outside those braces.
#include <iostream>

int main() {
    int x = 5;
    {
        int y = 10;
        std::cout << "x inside inner block: " << x << std::endl; // fine
        std::cout << "y inside inner block: " << y << std::endl; // fine
    }
    std::cout << "x outside: " << x << std::endl; // fine, x is main's own scope

    // std::cout << y << std::endl;  // <- uncomment: compiler error, y is out of scope here

    return 0;
}
