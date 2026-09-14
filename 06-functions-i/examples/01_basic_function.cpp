// A function that returns a value, and one that doesn't (void).
#include <iostream>
#include <string>

int add(int a, int b) {
    int sum = a + b;
    return sum;
}

void printGreeting(std::string name) {
    std::cout << "Hello, " << name << "!" << std::endl;
}

int main() {
    int result = add(3, 4);
    std::cout << "3 + 4 = " << result << std::endl;

    printGreeting("Kofi");

    return 0;
}
