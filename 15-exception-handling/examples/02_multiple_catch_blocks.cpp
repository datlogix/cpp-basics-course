// Different exception types can be caught differently, most-specific first.
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    std::vector<int> scores = {90, 85, 77};

    try {
        std::cout << scores.at(10) << std::endl; // throws std::out_of_range
    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Out of range: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Some other standard exception: " << e.what() << std::endl;
    }

    return 0;
}
