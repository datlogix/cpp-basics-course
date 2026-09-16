// nullptr means "points to nothing." Always check before dereferencing.
#include <iostream>

int main() {
    int* p = nullptr;

    if (p != nullptr) {
        std::cout << *p << std::endl;
    } else {
        std::cout << "p is null - nothing to read." << std::endl;
    }

    int value = 42;
    p = &value; // now p points to something real
    if (p != nullptr) {
        std::cout << "p now points to: " << *p << std::endl;
    }

    return 0;
}
