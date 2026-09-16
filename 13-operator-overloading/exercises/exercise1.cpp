// Exercise 1: Operator Overloading
//
// TODO 1: Build a class Fraction with private int numerator, denominator
//         and a constructor setting both.
// TODO 2: Overload operator+ to add two fractions the "cross multiply"
//         way: a/b + c/d = (a*d + c*b) / (b*d)  (don't worry about
//         simplifying the result).
// TODO 3: Overload operator== to compare two fractions using
//         cross-multiplication: a/b == c/d  when  a*d == c*b.
// TODO 4: Overload operator<< (as a friend free function) to print a
//         Fraction as "numerator/denominator".
// TODO 5: In main, create two Fractions, print their sum, and print
//         whether two fractions are equal.
//
// Compile and run:
//   g++ exercise1.cpp -o exercise1
//   ./exercise1
#include <iostream>

class Fraction {
private:
    // TODO: numerator, denominator

public:
    // TODO: constructor, operator+, operator==
    // TODO: friend std::ostream& operator<<(std::ostream&, const Fraction&);
};

int main() {
    // Your code here

    return 0;
}
