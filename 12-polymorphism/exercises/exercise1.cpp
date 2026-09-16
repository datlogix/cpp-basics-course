// Exercise 1: Polymorphism & Virtual Functions
//
// TODO 1: Write a base class Animal with a virtual method
//         std::string makeSound() returning "..." by default, and a
//         virtual destructor.
// TODO 2: Write derived classes Dog and Cat, each overriding
//         makeSound() to return "Woof" and "Meow" respectively.
// TODO 3: Build a std::vector<Animal*> containing one of each (allocated
//         with new).
// TODO 4: Loop over the vector and print each animal's makeSound()
//         result, proving the correct override runs for each.
// TODO 5: delete every pointer in the vector before returning.
//
// Compile and run:
//   g++ exercise1.cpp -o exercise1
//   ./exercise1
#include <iostream>
#include <string>
#include <vector>

class Animal {
public:
    // TODO: virtual std::string makeSound(), virtual destructor
};

class Dog : public Animal {
public:
    // TODO: override makeSound()
};

class Cat : public Animal {
public:
    // TODO: override makeSound()
};

int main() {
    // Your code here

    return 0;
}
