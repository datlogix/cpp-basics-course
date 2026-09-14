// if / else if / else - order matters, first matching branch wins.
#include <iostream>

int main() {
    int score = 72;

    if (score >= 90) {
        std::cout << "Grade: A" << std::endl;
    } else if (score >= 80) {
        std::cout << "Grade: B" << std::endl;
    } else if (score >= 70) {
        std::cout << "Grade: C" << std::endl;
    } else {
        std::cout << "Grade: F" << std::endl;
    }

    // Logical operators
    int age = 20;
    bool hasID = true;
    if (age >= 18 && hasID) {
        std::cout << "Allowed entry." << std::endl;
    } else {
        std::cout << "Entry denied." << std::endl;
    }

    return 0;
}
