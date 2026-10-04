// Capstone 3 - Smart Home Energy Management System
//
//   ./build/app           runs the interactive menu
//   ./build/app --demo    runs a scripted scenario with no keyboard input
#include "device.h"
#include "energy.h"
#include "errors.h"
#include "events.h"
#include "repository.h"
#include "statistics.h"

#include <iostream>
#include <string>

using namespace makersplace::energy;

// TODO (Stage 3): a class that owns the whole system (your "application"
// or "facade" object), created once here and passed to the menu and demo.
// Load saved data at start-up and save it before exiting.

void runDemo() {
    std::cout << "=== Smart Home Energy Management System - demo ===" << std::endl;
    Energy day = Energy::fromPower(150, 24) + Energy::fromPower(90, 5);
    std::cout << "  (starter check) fridge + TV for a day = " << day << std::endl;
    // TODO (Stage 3): a scripted scenario that exercises every feature:
    // loading data, the hierarchy, every pattern, the strong-guarantee
    // batch operation (including a failure), undo, reports, and saving.
}

void printMenu() {
    std::cout << std::endl << "Smart Home Energy Management System" << std::endl;
    std::cout << "  1. Show the house" << std::endl;
    std::cout << "  2. Switch a device on or off" << std::endl;
    std::cout << "  3. Simulate a sensor event" << std::endl;
    std::cout << "  4. Run the evening schedule" << std::endl;
    std::cout << "  5. Undo last app action" << std::endl;
    std::cout << "  6. Energy and cost report" << std::endl;
    std::cout << "  7. Change tariff" << std::endl;
    std::cout << "  8. Air conditioner controls" << std::endl;
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
