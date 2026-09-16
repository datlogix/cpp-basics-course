// & gets an address; * dereferences a pointer to get/set the value there.
#include <iostream>

int main() {
    int age = 25;
    int* agePtr = &age;

    std::cout << "age:            " << age << std::endl;
    std::cout << "&age (address): " << &age << std::endl;
    std::cout << "agePtr:         " << agePtr << std::endl;
    std::cout << "*agePtr:        " << *agePtr << std::endl;

    *agePtr = 30; // write through the pointer
    std::cout << "age after *agePtr = 30: " << age << std::endl;

    return 0;
}
