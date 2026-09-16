// Exercise 1: Inheritance
//
// TODO 1: Write a base class Vehicle with protected members
//         std::string make and int topSpeed, a constructor setting
//         both, and a method describe() that prints them.
// TODO 2: Write a derived class ElectricVehicle : public Vehicle that
//         adds a private member double batteryCapacityKwh and its own
//         constructor (calling Vehicle's constructor for make/topSpeed).
// TODO 3: Give ElectricVehicle its own describe() that prints everything
//         Vehicle's describe() would, PLUS the battery capacity.
// TODO 4: In main, create a Vehicle and an ElectricVehicle, call
//         describe() on both.
//
// Compile and run:
//   g++ exercise1.cpp -o exercise1
//   ./exercise1
#include <iostream>
#include <string>

class Vehicle {
protected:
    // TODO: make, topSpeed

public:
    // TODO: constructor, describe()
};

class ElectricVehicle : public Vehicle {
private:
    // TODO: batteryCapacityKwh

public:
    // TODO: constructor (calling Vehicle's constructor), describe()
};

int main() {
    // Your code here

    return 0;
}
