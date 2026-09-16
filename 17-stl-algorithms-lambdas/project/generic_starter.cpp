// Module 17 Project - Track A: Exam Score Analyzer
// See project/README.md for requirements.
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    const double MAX_SCORE = 80.0;

    int n;
    std::cout << "How many scores? ";
    std::cin >> n;

    std::vector<double> scores(n);
    for (int i = 0; i < n; i++) {
        std::cout << "Score " << i << " (out of " << MAX_SCORE << "): ";
        std::cin >> scores[i];
    }

    // TODO: sort scores, print them, and print the highest/lowest.

    // TODO: use transform to build a vector of percentages
    // (score / MAX_SCORE * 100.0), and print it.

    // TODO: use count_if to count how many students scored below 50%.

    return 0;
}
