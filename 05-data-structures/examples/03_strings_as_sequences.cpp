// std::string, revisited: it's also an indexable, loopable sequence.
#include <iostream>
#include <string>

int main() {
    std::string name = "Ama";

    std::cout << "First char: " << name[0] << std::endl;
    std::cout << "Length: " << name.length() << std::endl;

    name += "!";
    std::cout << "After append: " << name << std::endl;

    for (char c : name) {
        std::cout << c << std::endl;
    }

    return 0;
}
