// Default parameters and function overloading.
#include <iostream>
#include <string>

void greet(std::string name, std::string greeting = "Hello") {
    std::cout << greeting << ", " << name << "!" << std::endl;
}

int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

int main() {
    greet("Ama");
    greet("Kofi", "Good morning");

    std::cout << add(2, 3) << std::endl;      // calls int version
    std::cout << add(2.5, 3.1) << std::endl;  // calls double version

    return 0;
}
