// switch is a clean alternative to a long if/else if chain when
// comparing one variable against exact values. Never forget `break`.
#include <iostream>

int main() {
    char grade = 'B';

    switch (grade) {
        case 'A':
            std::cout << "Excellent" << std::endl;
            break;
        case 'B':
            std::cout << "Good" << std::endl;
            break;
        case 'C':
            std::cout << "Average" << std::endl;
            break;
        default:
            std::cout << "Unknown grade" << std::endl;
    }

    return 0;
}
