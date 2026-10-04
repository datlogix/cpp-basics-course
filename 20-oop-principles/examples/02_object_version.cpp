// The same school library written the OBJECT-ORIENTED way: each Book
// owns its own data and enforces its own rules.
//
// Compile and run:
//   g++ -std=c++17 -Wall -Wextra 02_object_version.cpp -o 02_object_version
//   ./02_object_version
#include <iostream>
#include <string>
#include <vector>

class Book {
private:
    std::string title;
    bool borrowed = false; // every Book starts available - can't be forgotten

public:
    Book(std::string t) : title(t) {}

    bool borrow() {
        if (borrowed) {
            return false; // already out - refuse
        }
        borrowed = true;
        return true;
    }

    void giveBack() { borrowed = false; }
    bool isBorrowed() const { return borrowed; }
    std::string getTitle() const { return title; }
};

class Library {
private:
    std::vector<Book> books;

public:
    void addBook(std::string title) {
        books.push_back(Book(title)); // title and status can never fall out of step
    }

    bool borrow(std::string title) {
        for (Book& b : books) {
            if (b.getTitle() == title) {
                return b.borrow();
            }
        }
        return false; // no such book
    }

    void printCatalogue() const {
        for (const Book& b : books) {
            std::cout << b.getTitle() << (b.isBorrowed() ? " (borrowed)" : " (available)")
                      << std::endl;
        }
    }
};

int main() {
    Library library;
    library.addBook("Things Fall Apart");
    library.addBook("Anowa");
    library.addBook("The Beautyful Ones Are Not Yet Born");

    library.borrow("Anowa");

    // Trying to borrow it again is refused BY THE BOOK ITSELF:
    if (!library.borrow("Anowa")) {
        std::cout << "Anowa is already borrowed." << std::endl;
    }

    // library.books[1] = ...;  // would not compile - books is private

    library.printCatalogue();
    return 0;
}
