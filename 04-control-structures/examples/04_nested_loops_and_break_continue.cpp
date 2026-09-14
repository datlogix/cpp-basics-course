// Nested loops (a multiplication grid), plus break and continue.
#include <iostream>

int main() {
    std::cout << "-- nested loops: multiplication grid --" << std::endl;
    for (int row = 1; row <= 3; row++) {
        for (int col = 1; col <= 3; col++) {
            std::cout << row * col << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "-- break and continue --" << std::endl;
    for (int i = 1; i <= 10; i++) {
        if (i == 7) break;            // stop the loop entirely once i is 7
        if (i % 2 == 0) continue;     // skip even numbers
        std::cout << i << std::endl;  // prints 1, 3, 5
    }

    return 0;
}
