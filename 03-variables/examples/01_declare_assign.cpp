// Declaration, initialization, and re-assignment.
#include <iostream>

int main() {
    int score = 0;          // initialization
    std::cout << "Start: " << score << std::endl;

    score = 10;              // re-assignment
    std::cout << "After = 10: " << score << std::endl;

    score += 5;               // shorthand for score = score + 5
    std::cout << "After += 5: " << score << std::endl;

    score++;                  // shorthand for score = score + 1
    std::cout << "After ++: " << score << std::endl;

    return 0;
}
