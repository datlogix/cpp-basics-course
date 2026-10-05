// C++ Foundations Project Book - Chapter 8, Activity 1: Library Book
// Difficulty: FOUNDATIONAL
//
// Use only: everything from Modules 1-7, plus classes with private member
// variables and public methods, constructors, getters and setters with
// validation, and this->.
// Not yet: inheritance (Part 2).
//
// Compile and run (from this folder):
//     g++ library_book.cpp -o library_book
//     ./library_book
#include <iostream>
#include <string>

class Book {
private:
    std::string title;
    std::string author;
    int year;
    bool isBorrowed;

public:
    // TODO 1: Every new book starts ON THE SHELF (not borrowed).
    Book(std::string title, std::string author, int year) {
    }

    // TODO 2: Refuse, with a clear message, if the book is already out.
    void borrowBook() {
    }

    // TODO 2: Refuse, with a clear message, if the book is already on the shelf.
    void returnBook() {
    }

    // TODO 3: One getter for every member. The first is written for you.
    std::string getTitle() {
        return title;
    }

    // TODO 3: Print every detail of the book, including where it is.
    void printInfo() {
    }
};

int main() {
    // TODO 4: Create three books, and show EVERY rule being enforced:
    //         borrow one twice, return one that is already on the shelf,
    //         and print each book's info before and after.

    return 0;
}
