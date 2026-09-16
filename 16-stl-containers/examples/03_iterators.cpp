// Iterators are the general mechanism behind range-based for loops.
#include <iostream>
#include <vector>

int main() {
    std::vector<int> scores = {90, 85, 77};

    // Explicit iterator loop:
    for (std::vector<int>::iterator it = scores.begin(); it != scores.end(); ++it) {
        std::cout << *it << std::endl;
    }

    // Same thing, using auto to avoid spelling out the iterator type:
    std::cout << "-- with auto --" << std::endl;
    for (auto it = scores.begin(); it != scores.end(); ++it) {
        std::cout << *it << std::endl;
    }

    // This is exactly what the range-based for loop below does for you:
    std::cout << "-- range-based for (equivalent) --" << std::endl;
    for (int score : scores) {
        std::cout << score << std::endl;
    }

    return 0;
}
