#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

const int MAX_LOANS = 2;

class LibraryError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class BookNotFoundError : public LibraryError {
public:
    using LibraryError::LibraryError;
};

class AlreadyBorrowedError : public LibraryError {
public:
    using LibraryError::LibraryError;
};

class LoanLimitError : public LibraryError {
private:
    std::string member;
    int limit;

public:
    LoanLimitError(std::string m, int lim)
        : LibraryError(m + " has reached the loan limit of " + std::to_string(lim)), member(m), limit(lim) {}
    std::string getMember() const { return member; }
    int getLimit() const { return limit; }
};

class Member {
private:
    std::string name;
    std::vector<std::string> loans;

public:
    explicit Member(std::string n) : name(n) {
        if (name.empty()) {
            throw std::invalid_argument("member name cannot be empty");
        }
    }
    std::string getName() const { return name; }
    int loanCount() const { return static_cast<int>(loans.size()); }
    void addLoan(const std::string& title) { loans.push_back(title); }
};

class Library {
private:
    std::map<std::string, bool> onShelf;
    std::map<std::string, Member> members;

    Member& findMember(const std::string& name) {
        auto it = members.find(name);
        if (it == members.end()) {
            throw std::out_of_range("no member called " + name);
        }
        return it->second;
    }

    void checkAvailable(const std::string& title) const {
        auto it = onShelf.find(title);
        if (it == onShelf.end()) {
            throw BookNotFoundError("the library has no book called '" + title + "'");
        }
        if (!it->second) {
            throw AlreadyBorrowedError("'" + title + "' is already on loan");
        }
    }

public:
    void addBook(const std::string& title) { onShelf[title] = true; }
    // emplace() inserts a new key/value pair. (members[name] = ... would need
    // Member to have a default constructor, which it deliberately doesn't.)
    void addMember(const std::string& name) { members.emplace(name, Member(name)); }

    void borrow(const std::string& memberName, const std::string& title) {
        Member& m = findMember(memberName);
        checkAvailable(title);
        if (m.loanCount() >= MAX_LOANS) {
            throw LoanLimitError(memberName, MAX_LOANS);
        }
        onShelf[title] = false;
        m.addLoan(title);
    }

    // STRONG guarantee: validate EVERYTHING first; only then change anything.
    void borrowMany(const std::string& memberName, const std::vector<std::string>& titles) {
        Member& m = findMember(memberName);
        for (size_t i = 0; i < titles.size(); i++) {
            checkAvailable(titles[i]);
            for (size_t j = 0; j < i; j++) {
                if (titles[j] == titles[i]) {
                    throw AlreadyBorrowedError("'" + titles[i] + "' appears twice in the request");
                }
            }
        }
        if (m.loanCount() + static_cast<int>(titles.size()) > MAX_LOANS) {
            throw LoanLimitError(memberName, MAX_LOANS);
        }
        // Commit. (vector::push_back could, in theory, run out of memory - for
        // a strict strong guarantee you would reserve space before this loop.)
        for (const std::string& t : titles) {
            onShelf[t] = false;
            m.addLoan(t);
        }
    }

    void printShelf() const {
        for (const auto& entry : onShelf) {
            std::cout << "  " << entry.first << (entry.second ? " (available)" : " (on loan)") << std::endl;
        }
    }
};

void tryBorrow(Library& lib, const std::string& who, const std::string& title) {
    try {
        lib.borrow(who, title);
        std::cout << who << " borrowed '" << title << "'" << std::endl;
    } catch (const LoanLimitError& e) {
        std::cout << "Refused: " << e.getMember() << " must return a book first (limit "
                  << e.getLimit() << ")" << std::endl;
    } catch (const LibraryError& e) {
        std::cout << "Refused: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

int main() {
    Library lib;
    lib.addBook("Things Fall Apart");
    lib.addBook("Anowa");
    lib.addBook("Arduino for Beginners");
    lib.addMember("Ama");
    lib.addMember("Kojo");

    try {
        lib.addMember("");
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    tryBorrow(lib, "Ama", "Anowa");
    tryBorrow(lib, "Kojo", "Anowa");
    tryBorrow(lib, "Kojo", "Harry Potter");
    tryBorrow(lib, "Yaw", "Things Fall Apart");
    tryBorrow(lib, "Ama", "Things Fall Apart");
    tryBorrow(lib, "Ama", "Arduino for Beginners");

    std::cout << "Kojo tries to borrow two books, one of which is already out:" << std::endl;
    try {
        lib.borrowMany("Kojo", {"Arduino for Beginners", "Things Fall Apart"});
    } catch (const LibraryError& e) {
        std::cout << "Refused: " << e.what() << std::endl;
    }
    lib.printShelf(); // Arduino for Beginners is still available - nothing changed
    return 0;
}
