// while, do-while, and for - three ways to repeat work.
#include <iostream>

int main() {
    std::cout << "-- while --" << std::endl;
    int count = 0;
    while (count < 5) {
        std::cout << count << std::endl;
        count++;
    }

    std::cout << "-- do-while (always runs the body at least once) --" << std::endl;
    int x = 100;
    do {
        std::cout << "x is " << x << std::endl;
        x++;
    } while (x < 100); // condition is already false, but the body still ran once

    std::cout << "-- for --" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << i << std::endl;
    }

    return 0;
}
