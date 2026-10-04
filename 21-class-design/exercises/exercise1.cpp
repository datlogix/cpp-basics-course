// Exercise 1: Class Design in Depth
//
// Build a ClockTime class representing a time of day on a 24-hour clock
// (for example 14:05). INVARIANT: hours is always 0..23 and minutes is
// always 0..59.
//
// TODO 1: Private members int hours and int minutes, each with a default
//         member initializer of 0.
// TODO 2: A main constructor ClockTime(int h, int m) that uses a member
//         initializer list, then validates: if h or m is out of range,
//         set the time to 00:00 instead.
// TODO 3: A delegating, explicit constructor ClockTime(int h) meaning
//         "h o'clock exactly" (minutes 0).
// TODO 4: const getters getHours() and getMinutes(), and a const method
//         void print() const that prints e.g. "09:05" (two digits each).
// TODO 5: A method void addMinutes(int m) that moves the time forward,
//         wrapping past midnight (23:50 + 20 minutes = 00:10). It must
//         keep the invariant true. Assume m >= 0.
// TODO 6: A static counter of how many ClockTime objects have been
//         created, with a static method static int created().
// TODO 7: Define print() and addMinutes() OUTSIDE the class body using
//         ClockTime::.
// TODO 8: In main, test every feature, including the wrap-around and an
//         invalid time like ClockTime(25, 70).
//
// Compile and run:
//   g++ -std=c++17 -Wall -Wextra exercise1.cpp -o exercise1
//   ./exercise1
#include <iostream>

class ClockTime {
    // Your code here
};

// TODO 7: out-of-class definitions here

int main() {
    // Your code here

    return 0;
}
