// C++ Foundations Project Book - Chapter 7, Activity 3: Recursion Lab
// Difficulty: CHALLENGE
//
// Use only: everything from Modules 1-6, plus reference parameters (&),
// default parameter values, function overloading and recursion.
// Not yet: classes (Module 8).
//
// Compile and run (from this folder):
//     g++ recursion_lab.cpp -o recursion_lab
//     ./recursion_lab
#include <iostream>
#include <string>

// Prototypes - definitions are below main.
void countDown(int n);
int fibonacci(int n);
int countChar(std::string s, char target, int index);
void printReverse(std::string s, int index);

int main() {
    // TODO 1: Test each recursive function with a few inputs, e.g.
    //         countDown(5);
    //         fibonacci(10) should be 55.
    //         countChar("banana", 'a', 0) should be 3.
    //         printReverse("hello", ...) should print olleh.

    // TODO 3: Draw the call tree for fibonacci(5) on paper or in a comment,
    //         and count the calls. Then add an int &calls parameter to
    //         fibonacci to check your count.

    // TODO 4: Write a LOOP version of fibonacci (e.g. fibonacciLoop) and
    //         run both for n = 30. Which is faster, and why? Answer here.

    return 0;
}

// TODO 2: Above each function, write its BASE CASE in a comment, and what
//         would happen without it.

void countDown(int n) {
    // TODO: print n down to 1, then "Liftoff!"
}

int fibonacci(int n) {
    // TODO: fibonacci(0) = 0, fibonacci(1) = 1,
    //       otherwise fibonacci(n - 1) + fibonacci(n - 2)
    return 0;
}

int countChar(std::string s, char target, int index) {
    // TODO: how many times does target appear from index onwards?
    return 0;
}

void printReverse(std::string s, int index) {
    // TODO: print s backwards. Which index should the first call start at?
}
