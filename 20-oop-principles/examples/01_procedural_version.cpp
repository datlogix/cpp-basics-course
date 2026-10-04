// A tiny school library written the PROCEDURAL way: data lives in
// parallel vectors, and free functions operate on them.
// Compare this with 02_object_version.cpp, which does the same job.
//
// Compile and run:
//   g++ -std=c++17 -Wall -Wextra 01_procedural_version.cpp -o 01_procedural_version
//   ./01_procedural_version
#include <iostream>
#include <string>
#include <vector>

// Two vectors that MUST always stay the same length and in the same
// order. Nothing in the language enforces that - only programmer care.
std::vector<std::string> titles;
std::vector<bool> isBorrowed;

void addBook(std::string title) {
    titles.push_back(title);
    isBorrowed.push_back(false); // forget this line and every book is wrong
}

bool borrowBook(int index) {
    if (isBorrowed[index]) {
        return false;
    }
    isBorrowed[index] = true;
    return true;
}

void printCatalogue() {
    for (size_t i = 0; i < titles.size(); i++) {
        std::cout << titles[i] << (isBorrowed[i] ? " (borrowed)" : " (available)")
                  << std::endl;
    }
}

int main() {
    addBook("Things Fall Apart");
    addBook("Anowa");
    addBook("The Beautyful Ones Are Not Yet Born");

    borrowBook(1);

    // Nothing stops ANY code from bypassing borrowBook()'s rule:
    isBorrowed[1] = false; // silently "returns" the book with no record

    printCatalogue();
    return 0;
}
