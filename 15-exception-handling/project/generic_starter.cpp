// Module 15 Project - Track A: Safe Grade Averager
// See project/README.md for requirements.
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    std::vector<double> validScores;

    std::cout << "Enter scores one at a time (0-100). Enter -1 to stop." << std::endl;

    while (true) {
        double score;
        std::cout << "Score: ";
        std::cin >> score;

        if (score == -1) break;

        try {
            // TODO: throw std::invalid_argument if score is outside 0-100.
            // Otherwise, push_back it into validScores.
        } catch (const std::invalid_argument& e) {
            std::cout << "Rejected: " << e.what() << std::endl;
        }
    }

    // TODO: compute and print the average of validScores (guard against
    // an empty vector).

    return 0;
}
