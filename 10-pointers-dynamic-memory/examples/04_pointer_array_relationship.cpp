// An array name decays into a pointer to its first element.
#include <iostream>

int main() {
    int scores[3] = {90, 85, 77};
    int* p = scores;

    std::cout << "*p:       " << *p << std::endl;       // 90, same as scores[0]
    std::cout << "*(p + 1): " << *(p + 1) << std::endl; // 85, same as scores[1]
    std::cout << "p[2]:     " << p[2] << std::endl;      // 77, pointer indexing works too

    return 0;
}
