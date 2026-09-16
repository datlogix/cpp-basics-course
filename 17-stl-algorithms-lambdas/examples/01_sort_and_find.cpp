// std::sort and std::find operate on a [begin, end) range from any container.
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> scores = {77, 92, 85, 60};

    std::sort(scores.begin(), scores.end());

    std::cout << "-- sorted --" << std::endl;
    for (int s : scores) {
        std::cout << s << std::endl;
    }

    auto it = std::find(scores.begin(), scores.end(), 85);
    if (it != scores.end()) {
        std::cout << "Found 85!" << std::endl;
    } else {
        std::cout << "Not found." << std::endl;
    }

    return 0;
}
