// std::cin >> reads a single word; std::getline reads a whole line.
#include <iostream>
#include <string>

int main() {
    std::string firstWordOnly;
    std::cout << "Type a single word: ";
    std::cin >> firstWordOnly;
    std::cout << "You typed: " << firstWordOnly << std::endl;

    // Clear the leftover newline before using getline, otherwise
    // getline immediately reads an empty leftover line.
    std::cin.ignore();

    std::string wholeLine;
    std::cout << "Now type a full sentence: ";
    std::getline(std::cin, wholeLine);
    std::cout << "You typed: " << wholeLine << std::endl;

    return 0;
}
