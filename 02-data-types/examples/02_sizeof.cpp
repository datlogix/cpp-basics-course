// See how many bytes of memory each type actually reserves.
#include <iostream>

int main() {
    std::cout << "int: "    << sizeof(int)    << " bytes" << std::endl;
    std::cout << "double: " << sizeof(double) << " bytes" << std::endl;
    std::cout << "float: "  << sizeof(float)  << " bytes" << std::endl;
    std::cout << "char: "   << sizeof(char)   << " bytes" << std::endl;
    std::cout << "bool: "   << sizeof(bool)   << " bytes" << std::endl;
    return 0;
}
