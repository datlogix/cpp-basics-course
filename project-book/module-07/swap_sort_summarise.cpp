// C++ Foundations Project Book - Chapter 7, Activity 1: Swap, Sort and Summarise
// Difficulty: FOUNDATIONAL
//
// Use only: everything from Modules 1-6, plus reference parameters (&),
// default parameter values, function overloading and recursion.
// Not yet: classes (Module 8).
//
// Compile and run (from this folder):
//     g++ swap_sort_summarise.cpp -o swap_sort_summarise
//     ./swap_sort_summarise
#include <iostream>
#include <vector>

// Prototypes - definitions are below main.
void swapValues(int &a, int &b);
void sortThree(int &a, int &b, int &c);
void summarise(std::vector<double> values, double &minimum, double &maximum, double &average);

int main() {
    // TODO 1: Prove swapValues works: print two variables, swap them,
    //         print them again.

    // TODO 2: Prove sortThree works with three numbers in the wrong order.

    // TODO 3: Make a vector of readings, call summarise, and print the
    //         three answers it hands back.

    // TODO 4: In a comment, explain what would happen to swapValues if you
    //         removed the & symbols, and why.

    return 0;
}

void swapValues(int &a, int &b) {
    // TODO 1
}

void sortThree(int &a, int &b, int &c) {
    // TODO 2: use swapValues - no new swapping code here.
}

void summarise(std::vector<double> values, double &minimum, double &maximum, double &average) {
    // TODO 3: what should happen if values is empty?
}
