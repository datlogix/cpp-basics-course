// A small project laid out the way real C++ projects are:
//   CMakeLists.txt, include/ for headers, src/ for source files.
//
// Build and run with CMake (from the 06_cmake_project folder):
//   cmake -S . -B build
//   cmake --build build
//   ./build/energy_report
//
// Or without CMake:
//   g++ -std=c++17 -Wall -Wextra -Iinclude src/main.cpp src/appliance.cpp -o energy_report
//   ./energy_report
// (-Iinclude does the same job as target_include_directories.)
#include "appliance.h"

#include <iostream>
#include <vector>

int main() {
    using makersplace::energy::Appliance; // a using-declaration, local to main

    std::vector<Appliance> home = {
        Appliance("Fridge", 150, 24),
        Appliance("Television", 90, 5),
        Appliance("Ceiling fan", 75, 10),
    };

    double total = 0;
    for (const Appliance& a : home) {
        std::cout << a.getName() << ": " << a.dailyKwh() << " kWh/day" << std::endl;
        total += a.dailyKwh();
    }
    std::cout << "Total: " << total << " kWh/day" << std::endl;
    return 0;
}
