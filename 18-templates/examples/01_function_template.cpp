// A function template writes logic once; the compiler generates a real
// version for whatever type you actually call it with.
#include <iostream>
#include <string>

template <typename T>
T maxOf(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    std::cout << maxOf(3, 7) << std::endl;                             // T = int
    std::cout << maxOf(3.5, 2.1) << std::endl;                          // T = double
    std::cout << maxOf(std::string("apple"), std::string("banana")) << std::endl; // T = std::string

    return 0;
}
