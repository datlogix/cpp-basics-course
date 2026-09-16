// erase() invalidates the iterator you used - it returns the next
// valid one, which is why this loop doesn't blindly ++it every time.
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};

    for (auto it = numbers.begin(); it != numbers.end(); ) {
        if (*it % 2 == 0) {
            it = numbers.erase(it); // removes it, returns next valid iterator
        } else {
            ++it;
        }
    }

    std::cout << "-- remaining (odd numbers only) --" << std::endl;
    for (int n : numbers) {
        std::cout << n << std::endl;
    }

    return 0;
}
