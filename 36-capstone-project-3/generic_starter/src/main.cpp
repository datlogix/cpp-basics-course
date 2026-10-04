// Capstone 3 - MakersPlace Academy Management System
//
//   ./build/app           runs the interactive menu
//   ./build/app --demo    runs a scripted scenario with no keyboard input
#include "person.h"
#include "money.h"
#include "errors.h"
#include "events.h"
#include "repository.h"
#include "statistics.h"

#include <iostream>
#include <string>

using namespace makersplace::school;

// TODO (Stage 3): a class that owns the whole system (your "application"
// or "facade" object), created once here and passed to the menu and demo.
// Load saved data at start-up and save it before exiting.

void runDemo() {
    std::cout << "=== MakersPlace Academy Management System - demo ===" << std::endl;
    Money fees = Money::fromCedis(1500) + Money::fromCedis(80);
    std::cout << "  (starter check) term fees + PTA dues = " << fees << std::endl;
    // TODO (Stage 3): a scripted scenario that exercises every feature:
    // loading data, the hierarchy, every pattern, the strong-guarantee
    // batch operation (including a failure), undo, reports, and saving.
}

void printMenu() {
    std::cout << std::endl << "MakersPlace Academy Management System" << std::endl;
    std::cout << "  1. List students" << std::endl;
    std::cout << "  2. Enrol a student in a course" << std::endl;
    std::cout << "  3. Record an assessment result" << std::endl;
    std::cout << "  4. Publish results" << std::endl;
    std::cout << "  5. Record a fee payment" << std::endl;
    std::cout << "  6. Undo last gradebook change" << std::endl;
    std::cout << "  7. Reports" << std::endl;
    std::cout << "  8. Change grading scheme" << std::endl;
    std::cout << "  0. Save and exit" << std::endl;
    std::cout << "Choice: ";
}

void runMenu() {
    int choice = -1;
    while (true) {
        printMenu();
        if (!(std::cin >> choice)) { // end of input, or not a number
            std::cout << std::endl;
            break;
        }
        if (choice == 0) {
            break;
        }
        switch (choice) {
            // TODO (Stage 3): one case per menu option, each wrapped so that
            // your exceptions are caught and reported without ending the program.
            default:
                std::cout << "Not implemented yet." << std::endl;
        }
    }
    std::cout << "Goodbye." << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--demo") {
        runDemo();
    } else {
        runMenu();
    }
    return 0;
}
