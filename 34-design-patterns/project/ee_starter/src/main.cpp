// Module 34 project - Track B: Smart Home Controller
// Design your classes in include/ and src/, then make this scenario run.
#include "events.h"

#include <iostream>
#include <string>
#include <vector>

int main() {
    // Configuration lines for the FACTORY: "kind,id,room,watts"
    std::vector<std::string> config = {
        "light,L1,Lounge,40",       "light,L2,Kitchen,60",  "socket,S1,Kitchen,0",
        "aircon,AC1,Bedroom,1500",  "motion,M1,Lounge,0",   "temperature,T1,Bedroom,0",
    };

    std::cout << "SCENARIO" << std::endl;
    std::cout << "1. Build the home from the config lines (Factory), arranged as" << std::endl;
    std::cout << "   house -> floors -> rooms -> devices (Composite), and print energy totals." << std::endl;
    std::cout << "2. Subscribe automations, the phone app and an event log to the sensors (Observer)." << std::endl;
    std::cout << "3. Motion in the lounge at 19:00 -> an automation switches L1 on." << std::endl;
    std::cout << "4. Bedroom temperature 31 C -> the air conditioner moves Off -> Cooling (State);" << std::endl;
    std::cout << "   a fault event moves it to Fault; it refuses Cooling until reset." << std::endl;
    std::cout << "5. From the app: switch L2 on, set AC1 to Eco, then undo both (Command)." << std::endl;
    std::cout << "6. Price the day with a flat tariff, then a time-of-use tariff (Strategy)." << std::endl;
    std::cout << "7. Plug in a third-party Fahrenheit sensor through an Adapter." << std::endl;

    (void)config; // TODO: remove when you use the config
    return 0;
}
