// A quick tour of the core built-in types.
#include <iostream>
#include <string>

int main() {
    int age = 21;
    double price = 19.99;
    char grade = 'A';
    bool isEnrolled = true;
    std::string name = "Ama";

    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Price: " << price << std::endl;
    std::cout << "Grade: " << grade << std::endl;
    std::cout << "Enrolled: " << isEnrolled << std::endl;

    return 0;
}
