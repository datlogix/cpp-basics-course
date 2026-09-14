// std::vector: a list that can grow and shrink at runtime.
#include <iostream>
#include <vector>

int main() {
    std::vector<int> scores = {90, 85, 77};
    scores.push_back(92);

    std::cout << "Size: " << scores.size() << std::endl;

    for (int i = 0; i < scores.size(); i++) {
        std::cout << "Score " << i << ": " << scores[i] << std::endl;
    }

    // Range-based for loop: cleaner when you don't need the index.
    std::cout << "-- range-based for --" << std::endl;
    for (int score : scores) {
        std::cout << score << std::endl;
    }

    scores.pop_back();
    std::cout << "Size after pop_back: " << scores.size() << std::endl;

    return 0;
}
