#include <iostream>
#include <memory>
#include <string>
#include <utility>
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
    std::vector<std::unique_ptr<Animal>> animals;

public:
    void admit(std::unique_ptr<Animal> a) {
        animals.push_back(std::move(a));
    }

    Animal* find(std::string name) {
        for (const std::unique_ptr<Animal>& a : animals) {
            if (a->getName() == name) {
                return a.get();
            }
        }
        return nullptr;
    }

    std::unique_ptr<Animal> rehome(std::string name) {
        for (size_t i = 0; i < animals.size(); i++) {
            if (animals[i]->getName() == name) {
                std::unique_ptr<Animal> leaving = std::move(animals[i]);
                animals.erase(animals.begin() + i);
                return leaving;
            }
        }
        return nullptr;
    }

    void roll() const {
        for (const std::unique_ptr<Animal>& a : animals) {
            std::cout << "  " << a->getName() << " says " << a->sound() << std::endl;
        }
    }

    // No destructor: each unique_ptr deletes its own Animal when the vector
    // is destroyed. Shelter now follows the Rule of Zero - and because
    // unique_ptr is move-only, Shelter automatically becomes move-only too,
    // so the dangerous copy can't even compile.
};

int main() {
    Shelter shelter;
    shelter.admit(std::make_unique<Dog>("Bingo"));
    shelter.admit(std::make_unique<Cat>("Kitty"));
    shelter.admit(std::make_unique<Dog>("Tiger"));

    shelter.roll();

    Animal* found = shelter.find("Kitty");
    if (found != nullptr) {
        std::cout << "Found " << found->getName() << std::endl;
    }

    std::unique_ptr<Animal> newHome = shelter.rehome("Tiger");
    if (newHome) {
        std::cout << newHome->getName() << " has been rehomed" << std::endl;
    }
    std::cout << "Still in the shelter:" << std::endl;
    shelter.roll();

    std::cout << "end of main:" << std::endl;
    return 0;
}
