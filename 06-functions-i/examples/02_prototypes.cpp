// A function prototype lets you call a function before its full
// definition appears later in the file.
#include <iostream>

double square(double x); // prototype

int main() {
    std::cout << square(5.0) << std::endl; // works because of the prototype above
    return 0;
}

double square(double x) { // full definition, after main
    return x * x;
}
