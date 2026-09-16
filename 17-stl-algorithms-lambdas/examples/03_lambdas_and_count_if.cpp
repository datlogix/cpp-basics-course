// A lambda is a small function written inline. count_if uses one as a
// predicate: a function returning true/false per element.
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> scores = {45, 72, 88, 30, 91, 55};

    auto isPassing = [](int score) {
        return score >= 50;
    };

    std::cout << "72 passing? " << isPassing(72) << std::endl;

    int numPassing = std::count_if(scores.begin(), scores.end(), isPassing);
    std::cout << "Passing count: " << numPassing << std::endl;

    // Or write the lambda directly inline, with no separate name at all:
    int numFailing = std::count_if(scores.begin(), scores.end(),
        [](int score) { return score < 50; });
    std::cout << "Failing count: " << numFailing << std::endl;

    return 0;
}
