// The same program as 01_single_file, split into point.h, point.cpp,
// and this main.cpp. main.cpp only sees the DECLARATIONS in point.h.
//
// Build and run (from inside this folder) - list every .cpp, never the .h:
//   g++ -std=c++17 -Wall -Wextra main.cpp point.cpp -o geometry
//   ./geometry
//
// Or see the two separate steps - compile each file, then link:
//   g++ -std=c++17 -Wall -Wextra -c point.cpp
//   g++ -std=c++17 -Wall -Wextra -c main.cpp
//   g++ point.o main.o -o geometry
//
// Try leaving point.cpp off the command line to see the linker's
// "undefined reference" error for yourself.
#include "point.h"

#include <iostream>

int main() {
    Point a(0, 0);
    Point b(3, 4);

    a.print();
    std::cout << " to ";
    b.print();
    std::cout << " is " << a.distanceTo(b) << " units" << std::endl;
    return 0;
}
