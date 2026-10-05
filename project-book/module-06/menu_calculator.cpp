// C++ Foundations Project Book - Chapter 6, Activity 2: Menu Calculator
// Difficulty: CORE
//
// Use only: everything from Modules 1-5, plus your own functions with
// parameters and return values, void functions, and prototypes.
// Parameters are passed by value.
// Not yet: reference parameters (&), default parameters, overloading or
// recursion (Module 7).
//
// Compile and run (from this folder):
//     g++ menu_calculator.cpp -o menu_calculator
//     ./menu_calculator
#include <iostream>
#include <string>

// Prototypes - definitions are below main.
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
void printMenu();
double readNumber(std::string prompt);

int main() {
    int choice = -1;

    // TODO 3: Loop until choice is 0:
    //         - call printMenu() and read the choice;
    //         - read two numbers with readNumber("First number: ") etc.;
    //         - use a switch on choice to call the right function;
    //         - print the result.

    // TODO 4: Before calling divide, check whether the second number is 0.
    //         If it is, print a clear message instead of dividing.

    return 0;
}

// TODO 1: Fill in the four arithmetic functions.
double add(double a, double b) {
    return 0;
}

double subtract(double a, double b) {
    return 0;
}

double multiply(double a, double b) {
    return 0;
}

double divide(double a, double b) {
    return 0;
}

// TODO 2: printMenu() only PRINTS the menu (1 = add ... 0 = exit).
void printMenu() {
}

// TODO 2: readNumber prints the prompt, reads a number and returns it.
double readNumber(std::string prompt) {
    return 0;
}
