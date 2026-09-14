// This file will NOT compile on purpose.
// Run: g++ 04_broken_missing_semicolon.cpp -o broken
// Read the error message g++ gives you, then compare it to the fixed
// version below (uncomment the semicolon and it compiles).
#include <iostream>

int main() {
    std::cout << "Missing a semicolon on this line" << std::endl
    return 0;
}
