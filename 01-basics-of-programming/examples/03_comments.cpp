// This whole line is a comment - the compiler skips it entirely.
#include <iostream>

/* This is a multi-line comment.
   Useful for longer explanations
   that span several lines. */
int main() {
    std::cout << "Comments don't affect what the program does." << std::endl;

    // Try deleting the two lines below and see what changes when you re-run.
    std::cout << "This line only appears because it's not commented out." << std::endl;

    return 0;
}
