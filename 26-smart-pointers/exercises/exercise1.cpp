// Exercise 1: Smart Pointers & Ownership
//
// This program works, but uses raw owning pointers: it has a delete loop
// in its destructor, and (because of the Rule of Three) it would break
// badly if a Shelter were ever copied. Convert it to smart pointers.
//
// TODO 1: Change the member to std::vector<std::unique_ptr<Animal>>.
// TODO 2: Change admit() to TAKE OWNERSHIP: it should accept a
//         std::unique_ptr<Animal> by value and move it into the vector.
// TODO 3: Delete Shelter's destructor entirely. Explain in a comment why
//         it's no longer needed (and which "Rule" the class now follows).
// TODO 4: Change find() to return a NON-OWNING Animal* (use .get()),
//         or nullptr if not found.
// TODO 5: Add std::unique_ptr<Animal> rehome(std::string name), which
//         removes the animal from the shelter and TRANSFERS ownership to
//         the caller (return nullptr if not found). Hint: std::move the
//         element out, then erase that position from the vector.
// TODO 6: Update main: create animals with std::make_unique, never write
//         new or delete, and rehome one animal into a local variable.
//         Show (with the destructor messages) that every animal is
//         deleted exactly once.
//
// Compile and run:
//   g++ -std=c++17 -Wall -Wextra exercise1.cpp -o exercise1
//   ./exercise1
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Animal {
protected:
    std::string name;

public:
    explicit Animal(std::string n) : name(n) {}
    virtual ~Animal() { std::cout << "  [-] " << name << std::endl; }
    std::string getName() const { return name; }
    virtual std::string sound() const { return "..."; }
};

class Dog : public Animal {
public:
    explicit Dog(std::string n) : Animal(n) {}
    std::string sound() const override { return "Woof"; }
};

class Cat : public Animal {
public:
    explicit Cat(std::string n) : Animal(n) {}
    std::string sound() const override { return "Meow"; }
};

class Shelter {
private:
    std::vector<Animal*> animals; // TODO 1

public:
    void admit(Animal* a) { // TODO 2
        animals.push_back(a);
    }

    Animal* find(std::string name) { // TODO 4
        for (Animal* a : animals) {
            if (a->getName() == name) {
                return a;
            }
        }
        return nullptr;
    }

    // TODO 5: rehome()

    void roll() const {
        for (Animal* a : animals) {
            std::cout << "  " << a->getName() << " says " << a->sound() << std::endl;
        }
    }

    ~Shelter() { // TODO 3
        for (Animal* a : animals) {
            delete a;
        }
    }
};

int main() {
    Shelter shelter;
    shelter.admit(new Dog("Bingo"));
    shelter.admit(new Cat("Kitty"));
    shelter.admit(new Dog("Tiger"));

    shelter.roll();

    Animal* found = shelter.find("Kitty");
    if (found != nullptr) {
        std::cout << "Found " << found->getName() << std::endl;
    }

    // TODO 6: rehome "Tiger" into a local std::unique_ptr<Animal> here.

    std::cout << "end of main:" << std::endl;
    return 0;
}
