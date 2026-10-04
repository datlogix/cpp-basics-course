// Exercise 1: Templates Meet OOP
//
// Build ONE generic Repository class that can store students, books,
// sensors... anything that has an ID.
//
// TODO 1: Write a C++20 concept HasId: a type T satisfies it if, for a
//         const T& item, item.getId() compiles and converts to std::string.
// TODO 2: Write a class template
//             template <HasId T, int MaxItems> class Repository
//         storing items in a std::vector<T>, with these members DECLARED
//         inside the class and DEFINED outside it (template <...> and
//         Repository<T, MaxItems>:: on each):
//           void add(const T& item)   - throws std::invalid_argument for a
//                                       duplicate ID, std::length_error when
//                                       MaxItems items are already stored
//           T* find(const std::string& id)  - nullptr if not found
//           bool remove(const std::string& id)
//           int size() const
// TODO 3: Add a MEMBER FUNCTION TEMPLATE
//             template <typename Predicate> int countIf(Predicate p) const
//         that counts the items for which p(item) is true. Write it inside
//         the class.
// TODO 4: In main, create a Repository<Student, 3> and a Repository<Book, 10>,
//         and exercise every member - including the duplicate and the
//         "full" errors, and countIf with a lambda.
// TODO 5: Write (and leave commented out) a line that tries to make a
//         Repository<int, 5>, and paste the compiler's error message into a
//         comment underneath it.
//
// Compile and run (C++20 for concepts):
//   g++ -std=c++20 -Wall -Wextra exercise1.cpp -o exercise1
//   ./exercise1
#include <concepts>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Student {
private:
    std::string id;
    std::string name;
    double average;

public:
    Student(std::string i, std::string n, double avg) : id(i), name(n), average(avg) {}
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    double getAverage() const { return average; }
};

class Book {
private:
    std::string isbn;
    std::string title;
    bool borrowed = false;

public:
    Book(std::string i, std::string t) : isbn(i), title(t) {}
    std::string getId() const { return isbn; }
    std::string getTitle() const { return title; }
    bool isBorrowed() const { return borrowed; }
    void borrow() { borrowed = true; }
};

// TODO 1

// TODO 2 and 3

int main() {
    // TODO 4 and 5

    return 0;
}
