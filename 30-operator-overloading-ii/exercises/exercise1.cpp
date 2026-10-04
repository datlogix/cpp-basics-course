// Exercise 1: Operator Overloading II & Friends
//
// Build a Fraction value type that behaves like a built-in number.
// INVARIANT: the denominator is always positive, and the fraction is
// always stored in lowest terms (e.g. 2/4 is stored as 1/2, 3/-6 as -1/2).
// reduce() (provided) restores the invariant.
//
// TODO 1: Compound assignment members: +=, -=, *= (each returns *this by
//         reference and calls reduce()).
// TODO 2: Binary NON-member operators +, -, * written in terms of TODO 1.
//         Also make  Fraction * int  AND  int * Fraction  both work.
// TODO 3: Prefix and postfix ++ (add exactly 1).
// TODO 4: A friend operator<< printing "3/4" (or just "2" when the
//         denominator is 1).
// TODO 5: A friend operator>> that reads the form "3/4". If the input is
//         malformed or the denominator is 0, leave the Fraction unchanged
//         and put the stream into a failed state with
//         in.setstate(std::ios::failbit);
// TODO 6: explicit operator double() for the decimal value.
// TODO 7: Comparisons with C++20 <=> and ==. (Hint: compare a/b with c/d
//         by comparing a*d with c*b - this works because denominators
//         are always positive.)
// TODO 8: Uncomment the tests in main.
//
// Compile and run (C++20 for <=>):
//   g++ -std=c++20 -Wall -Wextra exercise1.cpp -o exercise1
//   ./exercise1
#include <algorithm>
#include <compare>
#include <iostream>
#include <numeric> // std::gcd
#include <sstream>
#include <vector>

class Fraction {
private:
    long num;
    long den;

    void reduce() {
        if (den < 0) {
            num = -num;
            den = -den;
        }
        long g = std::gcd(num, den);
        if (g != 0) {
            num /= g;
            den /= g;
        }
    }

public:
    Fraction(long n = 0, long d = 1) : num(n), den(d == 0 ? 1 : d) { reduce(); }

    long numerator() const { return num; }
    long denominator() const { return den; }

    // TODO 1, 3, 4, 5, 6, 7
};

// TODO 2

int main() {
    // Fraction half(1, 2), third(1, 3);
    // std::cout << half << " + " << third << " = " << half + third << std::endl;   // 5/6
    // std::cout << half << " - " << third << " = " << half - third << std::endl;   // 1/6
    // std::cout << "3 * 1/3 = " << 3 * third << ", 1/3 * 3 = " << third * 3 << std::endl; // 1, 1
    //
    // Fraction f(3, 4);
    // std::cout << "f++ gives " << f++ << ", then f is " << f << std::endl;  // 3/4, 7/4
    // std::cout << "++f gives " << ++f << std::endl;                          // 11/4
    // std::cout << "as decimal: " << static_cast<double>(f) << std::endl;    // 2.75
    //
    // std::istringstream input("2/6 5/0 7/8");
    // Fraction a, b(9, 9);
    // input >> a;
    // std::cout << "read " << a << std::endl;                                 // 1/3
    // if (!(input >> b)) { std::cout << "5/0 rejected, b is still " << b << std::endl; } // 1
    //
    // std::vector<Fraction> v = {Fraction(3, 4), Fraction(1, 2), Fraction(5, 6), Fraction(2, 4)};
    // std::sort(v.begin(), v.end());
    // for (const Fraction& x : v) { std::cout << x << " "; }                   // 1/2 1/2 3/4 5/6
    // std::cout << std::endl << "1/2 == 2/4 ? " << (Fraction(1, 2) == Fraction(2, 4)) << std::endl; // 1
    return 0;
}
