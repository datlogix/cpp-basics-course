// All four pillars of OOP in one short program, each labelled.
//
// Compile and run:
//   g++ -std=c++17 -Wall -Wextra 03_four_pillars.cpp -o 03_four_pillars
//   ./03_four_pillars
#include <iostream>
#include <string>
#include <vector>

// PILLAR 3 - INHERITANCE: LibraryItem is the general idea; Book and
// Magazine are more specific kinds of it ("is-a").
class LibraryItem {
private:
    // PILLAR 1 - ENCAPSULATION: data is private; only methods can change it.
    std::string title;
    int daysBorrowed = 0;

public:
    LibraryItem(std::string t) : title(t) {}
    virtual ~LibraryItem() {}

    void borrowFor(int days) {
        if (days > 0) { // the class guards its own rule
            daysBorrowed = days;
        }
    }

    std::string getTitle() const { return title; }
    int getDaysBorrowed() const { return daysBorrowed; }

    // PILLAR 2 - ABSTRACTION: callers ask "what is the late fee?" without
    // knowing HOW each kind of item calculates it.
    // PILLAR 4 - POLYMORPHISM: virtual lets each derived class answer differently.
    virtual double lateFee(int daysLate) const {
        return daysLate * 0.50;
    }
};

class Book : public LibraryItem {
public:
    Book(std::string t) : LibraryItem(t) {}
    double lateFee(int daysLate) const override {
        return daysLate * 1.00; // books cost GHS 1.00 per day late
    }
};

class Magazine : public LibraryItem {
public:
    Magazine(std::string t) : LibraryItem(t) {}
    double lateFee(int daysLate) const override {
        return daysLate * 0.20; // magazines are cheaper
    }
};

int main() {
    std::vector<LibraryItem*> items;
    items.push_back(new Book("Things Fall Apart"));
    items.push_back(new Magazine("Junior Graphic"));

    // POLYMORPHISM in action: one loop, the correct lateFee() for each item.
    for (LibraryItem* item : items) {
        std::cout << item->getTitle() << " - 3 days late costs GHS "
                  << item->lateFee(3) << std::endl;
    }

    for (LibraryItem* item : items) {
        delete item;
    }
    return 0;
}
