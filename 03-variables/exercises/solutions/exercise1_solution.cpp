#include <iostream>
#include <string>

int main() {
    std::string name;
    std::cout << "What's your name? ";
    std::cin >> name;

    int age;
    std::cout << "How old are you? ";
    std::cin >> age;

    const int LEGAL_AGE = 18;
    int yearsSinceLegalAge = age - LEGAL_AGE;

    std::cout << name << ", you turned " << LEGAL_AGE << " "
              << yearsSinceLegalAge << " years ago." << std::endl;

    return 0;
}
