// C++ Foundations Project Book - Chapter 3, Activity 3: Scope Detective
// Difficulty: CHALLENGE
//
// Use only: everything from Modules 1-2, plus const, +=, -=, *=, ++ and --,
// reading input with std::cin >> and std::getline, and { } blocks.
// Not yet: if/else, switch or loops (Module 4).
//
// Compile and run (from this folder):
//     g++ scope_detective.cpp -o scope_detective
//     ./scope_detective
#include <iostream>

int main() {
    int count = 10;

    {
        // TODO 1: Declare a NEW int count = 99; here, and print it.

        // TODO 3 (later): declare int bonus = 5; here.
    }

    // TODO 1 (continued): Print count again here, after the block has closed.

    // TODO 2: BEFORE you run the program, write a comment predicting what
    //         each print will show. Then run it. Were you right?

    // TODO 3: Try to print bonus here, outside its block. Copy the
    //         compiler's message into a comment and explain it in your own
    //         words. Then delete that line so the program compiles again.

    // TODO 4: Design one more experiment showing that an inner block CAN
    //         read and change a variable declared outside it (like count).
    //         Comment on what you see.

    return 0;
}
