// C++ Foundations Project Book - Chapter 2, Activity 3: Memory Map
// Difficulty: CHALLENGE
//
// Use only: everything from Module 1, plus variables of type int, double,
// char, bool and std::string whose values are written into the code,
// arithmetic (+ - * /), sizeof and static_cast.
// Not yet: reading input (Module 3), or if/else and loops (Module 4).
//
// Compile and run (from this folder):
//     g++ memory_map.cpp -o memory_map
//     ./memory_map
#include <iostream>
#include <string>

int main() {
    // TODO 1: Use sizeof to print the size in bytes of int, double, float,
    //         char, bool and std::string. One has been done for you:
    std::cout << "int: " << sizeof(int) << " bytes" << std::endl;

    // TODO 2: A robot stores 1000 temperature readings. Calculate and print
    //         how many bytes they take as double, how many as float, and
    //         the difference between the two.

    // TODO 3: Store 9.99 in an int AND in a double, and print both.

    // TODO 4: Print static_cast<int>('A'). Explain both results (TODO 3
    //         and TODO 4) in comments.

    // TODO 5: Finish with a comment block: for the robot's readings, would
    //         you choose float or double, and why?

    return 0;
}
