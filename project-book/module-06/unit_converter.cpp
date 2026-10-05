// C++ Foundations Project Book - Chapter 6, Activity 1: Unit Converter Library
// Difficulty: FOUNDATIONAL
//
// Use only: everything from Modules 1-5, plus your own functions with
// parameters and return values, void functions, and prototypes.
// Parameters are passed by value.
// Not yet: reference parameters (&), default parameters, overloading or
// recursion (Module 7).
//
// Compile and run (from this folder):
//     g++ unit_converter.cpp -o unit_converter
//     ./unit_converter
#include <iostream>

// TODO 1: Store the cedi-to-dollar exchange rate in a const double here.

// Prototypes - one is written for you. Add at least four more, each taking
// one double and returning a double: e.g. milesToKm, kgToPounds,
// metresToFeet, cedisToDollars.
// TODO 4: Above each prototype, write a one-line comment saying what it
//         takes and what it returns, like this one:

// Takes a distance in kilometres; returns the same distance in miles.
double kmToMiles(double km);

int main() {
    // TODO 3: Call EACH function at least twice with different values, and
    //         print clearly labelled results, e.g.
    //         std::cout << "10 km = " << kmToMiles(10) << " miles" << std::endl;

    return 0;
}

// TODO 2: Write the full definition of every function below main.

double kmToMiles(double km) {
    // TODO: 1 km is about 0.621371 miles.
    return 0;
}
