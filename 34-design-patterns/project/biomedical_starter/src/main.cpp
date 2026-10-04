// Module 34 project - Track C: Ward Monitoring Platform
// Design your classes in include/ and src/, then make this scenario run.
#include "events.h"

#include <iostream>
#include <string>
#include <vector>

int main() {
    // Configuration lines for the FACTORY: "kind,bed,serial"
    std::vector<std::string> config = {
        "pulse,Bed 1,PO-101",   "thermometer,Bed 1,TH-101", "pulse,Bed 2,PO-102",
        "thermometer,Bed 2,TH-102", "pump,Bed 2,IP-201",
    };

    std::cout << "SCENARIO" << std::endl;
    std::cout << "1. Create the monitors from the config lines (Factory)." << std::endl;
    std::cout << "2. Wrap Bed 2's thermometer with smoothing and logging (Decorator)." << std::endl;
    std::cout << "3. Subscribe the nurse station, the early warning calculator and the chart log (Observer)." << std::endl;
    std::cout << "4. Record a round of vital signs - every listener reacts." << std::endl;
    std::cout << "5. Score Bed 2 with the adult scheme, then the paediatric scheme (Strategy)." << std::endl;
    std::cout << "6. Start Bed 2's pump; an occlusion moves it to Alarm; it refuses to restart" << std::endl;
    std::cout << "   until the alarm is cleared (State)." << std::endl;
    std::cout << "7. Chart two medication doses; undo one with a reason (Command)." << std::endl;

    (void)config; // TODO: remove when you use the config
    return 0;
}
