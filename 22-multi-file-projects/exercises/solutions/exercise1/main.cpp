// Build and run (from inside this folder):
//   g++ -std=c++17 -Wall -Wextra main.cpp gradebook.cpp -o gradebook
//   ./gradebook
// Or with CMake:
//   cmake -S . -B build && cmake --build build && ./build/gradebook
#include "gradebook.h"

int main() {
    school::Gradebook maths("Mathematics");
    maths.addResult("Akosua", 84);
    maths.addResult("Kwabena", 67);
    maths.addResult("Selorm", 72);
    maths.addResult("Invalid", 140); // rejected

    maths.print();
    return 0;
}
