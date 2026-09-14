// Fixed-size arrays: indexing starts at 0, size is fixed at compile time.
#include <iostream>

int main() {
    const int SIZE = 5;
    int scores[SIZE] = {90, 85, 77, 92, 60};

    std::cout << "First: " << scores[0] << std::endl;
    std::cout << "Last: "  << scores[SIZE - 1] << std::endl;

    for (int i = 0; i < SIZE; i++) {
        std::cout << "Score " << i << ": " << scores[i] << std::endl;
    }

    return 0;
}
