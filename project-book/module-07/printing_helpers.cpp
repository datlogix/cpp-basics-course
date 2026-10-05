// C++ Foundations Project Book - Chapter 7, Activity 2: Printing Helpers
// Difficulty: CORE
//
// Use only: everything from Modules 1-6, plus reference parameters (&),
// default parameter values, function overloading and recursion.
// Not yet: classes (Module 8).
//
// Compile and run (from this folder):
//     g++ printing_helpers.cpp -o printing_helpers
//     ./printing_helpers
#include <iostream>
#include <string>

// Prototypes - definitions are below main.
// Default values go in the PROTOTYPE only. Don't repeat them in the
// definition below main, or the compiler will complain.
void printLine(int length = 30, char symbol = '-');
void printBoxed(std::string text, char border = '*');

// TODO 2: Write four overloaded prototypes called printValue: one for an
//         int, one for a double, one for a std::string, and one for a bool
//         (which prints "yes" or "no"). The first is written for you.
void printValue(int value);

int main() {
    // TODO 1: Call printLine three ways: with no arguments, with only a
    //         length, and with both a length and a symbol.

    // TODO 4: Use your helpers to print a small report card for one
    //         student (name, age, average, passed?).

    // TODO 5: In a comment, explain how the compiler decides which
    //         printValue to call.

    return 0;
}

void printLine(int length, char symbol) {
    // TODO 1
}

void printValue(int value) {
    // TODO 2
}

void printBoxed(std::string text, char border) {
    // TODO 3: the box must be exactly the right width for text.
    //         text.length() tells you how many characters it has.
}
