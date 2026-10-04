// Exercise 1: Object Lifetime, Destructors & RAII
//
// PART A - Tracing
// TODO 1: Complete class Tracer so that its constructor prints
//         "enter <name>" and its destructor prints "leave <name>".
// TODO 2: BEFORE running, write down (in the comment block marked
//         PREDICTION) the exact output you expect from partA().
//         Then run the program and correct any mistakes in your
//         prediction - and explain each correction in one line.
//
// PART B - An RAII class that owns heap memory
// TODO 3: Complete class ReadingBuffer:
//           - The constructor takes a capacity, allocates
//             new double[capacity], and prints "allocated <capacity>".
//           - bool add(double value) stores a value, returning false if
//             the buffer is full.
//           - double average() const returns the average of the stored
//             values (0 if empty).
//           - The destructor releases the array with delete[] and prints
//             "freed <capacity>".
//           - Do NOT copy ReadingBuffer objects (Module 24 explains why).
// TODO 4: Complete processReadings() so that it RETURNS EARLY (before
//         printing the average) if any reading is negative. Run it with
//         both data sets in main, and confirm "freed" is printed in BOTH
//         cases - with no manual delete anywhere in processReadings().
//
// Compile and run:
//   g++ -std=c++17 -Wall -Wextra exercise1.cpp -o exercise1
//   ./exercise1
#include <iostream>
#include <string>
#include <vector>

class Tracer {
private:
    std::string name;

public:
    explicit Tracer(std::string n) : name(n) {
        // TODO 1: print "enter <name>"
    }

    // TODO 1: add a destructor that prints "leave <name>"
};

void partA() {
    Tracer a("a");
    for (int i = 0; i < 2; i++) {
        Tracer loop("loop" + std::to_string(i));
    }
    Tracer b("b");
}

/*
  PREDICTION for partA():

*/

class ReadingBuffer {
    // TODO 3
};

void processReadings(const std::vector<double>& readings) {
    // TODO 4: create a ReadingBuffer sized readings.size(), add each
    // reading - returning early on a negative one - then print the average.
    (void)readings; // remove this line when you use readings
}

int main() {
    std::cout << "--- Part A ---" << std::endl;
    partA();

    std::cout << "--- Part B: good data ---" << std::endl;
    processReadings({36.6, 36.9, 37.2});

    std::cout << "--- Part B: bad data ---" << std::endl;
    processReadings({36.6, -1.0, 37.2});

    return 0;
}
