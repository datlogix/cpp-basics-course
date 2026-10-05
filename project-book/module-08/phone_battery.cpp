// C++ Foundations Project Book - Chapter 8, Activity 2: Phone Battery Simulator
// Difficulty: CORE
//
// Use only: everything from Modules 1-7, plus classes with private member
// variables and public methods, constructors, getters and setters with
// validation, and this->.
// Not yet: inheritance (Part 2).
//
// The rule this class must protect: the percentage is ALWAYS between 0
// and 100, however the phone is used.
//
// Compile and run (from this folder):
//     g++ phone_battery.cpp -o phone_battery
//     ./phone_battery
#include <iostream>
#include <string>

class Battery {
private:
    int percentage;

public:
    // TODO 1: If startPercentage is below 0 or above 100, bring it back
    //         into range before storing it.
    Battery(int startPercentage) {
        percentage = 0;
    }

    // TODO 2: Drain 1% for every 3 minutes of use. Never go below 0.
    void use(int minutes) {
    }

    // TODO 2: Add 2% per minute of charging. Never go above 100.
    void charge(int minutes) {
    }

    // TODO 3
    int getPercentage() {
        return 0;
    }

    // TODO 3: Return "Full", "Good", "Low" or "Empty". You decide the
    //         boundaries - store them as const int values.
    std::string status() {
        return "";
    }
};

int main() {
    // TODO 4: Simulate a day with a loop of mixed use and charging,
    //         printing the percentage and status after every step.

    // TODO 5: Try to break the rule from main (e.g. use(10000), charge(500),
    //         Battery(150)). The percentage should stay between 0 and 100.

    return 0;
}
