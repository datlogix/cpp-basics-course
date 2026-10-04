#include "panel.h"

#include <iostream>
#include <sstream>

using namespace makersplace::energy;

int main() {
    Panel panel;
    panel.addCircuit("kitchen", 20);
    panel.addCircuit("lounge", 10);

    // Stands in for a CSV file. Line 3 is corrupted and line 5 names an unknown circuit.
    std::istringstream csv("kitchen,Kettle,2200\n"
                           "kitchen,Microwave,1100\n"
                           "kitchen,Fridge,lots\n"
                           "lounge,Television,90\n"
                           "garage,Welder,5000\n"
                           "lounge,Air conditioner,1500\n");
    try {
        int loaded = panel.loadAppliances(csv);
        std::cout << "Loaded " << loaded << " appliances" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Loading stopped: " << e.what() << "  <- TODO: one bad line must not stop the rest"
                  << std::endl;
    }

    // TODO: an 18:00 schedule that switches on the kettle, microwave and AC.
    // Show applySchedule() refusing it (OvercurrentError - use its data) and
    // the panel left exactly as it was; then apply a safe schedule.
    panel.print();
    return 0;
}
