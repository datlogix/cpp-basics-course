// Capstone 3 - Hospital Ward Patient Monitoring System
//
//   ./build/app           runs the interactive menu
//   ./build/app --demo    runs a scripted scenario with no keyboard input
#include "medical_device.h"
#include "dose.h"
#include "errors.h"
#include "events.h"
#include "repository.h"
#include "statistics.h"

#include <iostream>
#include <string>

using namespace makersplace::clinic;

// TODO (Stage 3): a class that owns the whole system (your "application"
// or "facade" object), created once here and passed to the menu and demo.
// Load saved data at start-up and save it before exiting.

void runDemo() {
    std::cout << "=== Hospital Ward Patient Monitoring System - demo ===" << std::endl;
    Dose daily = Dose::mg(500) + Dose::mg(500);
    std::cout << "  (starter check) two 500 mg doses = " << daily << std::endl;
    // TODO (Stage 3): a scripted scenario that exercises every feature:
    // loading data, the hierarchy, every pattern, the strong-guarantee
    // batch operation (including a failure), undo, reports, and saving.
}

void printMenu() {
    std::cout << std::endl << "Hospital Ward Patient Monitoring System" << std::endl;
    std::cout << "  1. Show the wards" << std::endl;
    std::cout << "  2. Admit a patient" << std::endl;
    std::cout << "  3. Transfer a patient" << std::endl;
    std::cout << "  4. Record vital signs" << std::endl;
    std::cout << "  5. Ward round: prescribe orders" << std::endl;
    std::cout << "  6. Undo last chart entry" << std::endl;
    std::cout << "  7. Infusion pump controls" << std::endl;
    std::cout << "  8. Shift handover report" << std::endl;
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
