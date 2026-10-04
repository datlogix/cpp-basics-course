// Exercise 1: Exceptions in Class Design
//
// A school library lends books to members. Each member may hold at most
// MAX_LOANS books at once.
//
// TODO 1: Build an exception hierarchy:
//           LibraryError : public std::runtime_error   (the root)
//           BookNotFoundError : public LibraryError
//           AlreadyBorrowedError : public LibraryError
//           LoanLimitError : public LibraryError - carries the member's
//             name and the limit, with getters, and builds its own message.
// TODO 2: Member's constructor must throw std::invalid_argument for an
//         empty name.
// TODO 3: Library::borrow(memberName, title) must throw the right
//         exception for: unknown member (BookNotFoundError is wrong here -
//         use std::out_of_range), unknown title, a book already out, and a
//         member at the limit.
// TODO 4: Library::borrowMany(memberName, titles) must give the STRONG
//         guarantee: either every book in the list is borrowed, or (if any
//         one fails) NONE are, and the exception still reaches the caller.
//         Hint: check everything first, THEN change anything.
// TODO 5: In main, use try/catch blocks ordered from most to least specific
//         to show each error, using LoanLimitError's data in its message.
//         Show that a failed borrowMany() left every book available.
//
// Compile and run:
//   g++ -std=c++17 -Wall -Wextra exercise1.cpp -o exercise1
//   ./exercise1
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

const int MAX_LOANS = 2;

// TODO 1: exception classes

class Member {
private:
    std::string name;
    std::vector<std::string> loans;

public:
    explicit Member(std::string n) : name(n) {
        // TODO 2
    }
    std::string getName() const { return name; }
    int loanCount() const { return static_cast<int>(loans.size()); }
    void addLoan(const std::string& title) { loans.push_back(title); }
};

class Library {
private:
    std::map<std::string, bool> onShelf;   // title -> available?
    std::map<std::string, Member> members; // name -> member

public:
    void addBook(const std::string& title) { onShelf[title] = true; }
    // emplace() inserts a new key/value pair. (members[name] = ... would need
    // Member to have a default constructor, which it deliberately doesn't.)
    void addMember(const std::string& name) { members.emplace(name, Member(name)); }

    void borrow(const std::string& memberName, const std::string& title) {
        // TODO 3
        (void)memberName;
        (void)title;
    }

    void borrowMany(const std::string& memberName, const std::vector<std::string>& titles) {
        // TODO 4
        (void)memberName;
        (void)titles;
    }

    void printShelf() const {
        for (const auto& entry : onShelf) {
            std::cout << "  " << entry.first << (entry.second ? " (available)" : " (on loan)") << std::endl;
        }
    }
};

int main() {
    // TODO 5

    return 0;
}
