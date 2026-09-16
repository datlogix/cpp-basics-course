#include <iostream>
#include <string>
#include <vector>

class Animal {
public:
    virtual std::string makeSound() {
        return "...";
    }
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    std::string makeSound() override {
        return "Woof";
    }
};

class Cat : public Animal {
public:
    std::string makeSound() override {
        return "Meow";
    }
};

int main() {
    std::vector<Animal*> animals;
    animals.push_back(new Dog());
    animals.push_back(new Cat());

    for (Animal* a : animals) {
        std::cout << a->makeSound() << std::endl;
    }

    for (Animal* a : animals) {
        delete a;
    }

    return 0;
}
