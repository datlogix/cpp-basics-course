// Recursion: a function that calls itself, with a base case that stops it.
#include <iostream>

int factorial(int n) {
    if (n <= 1) {                  // base case
        return 1;
    }
    return n * factorial(n - 1);   // recursive case: moves toward the base case
}

int fibonacci(int n) {
    if (n <= 1) {                  // base case
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2); // recursive case
}

int main() {
    for (int i = 1; i <= 6; i++) {
        std::cout << i << "! = " << factorial(i) << std::endl;
    }

    std::cout << "-- fibonacci --" << std::endl;
    for (int i = 0; i < 8; i++) {
        std::cout << fibonacci(i) << " ";
    }
    std::cout << std::endl;

    return 0;
}
