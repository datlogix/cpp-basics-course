// Module 14 Project - Track C: Patient Vitals Log
// See project/README.md for requirements.
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    const double LOW_HEART_RATE = 60.0;
    const double HIGH_HEART_RATE = 100.0;

    std::string patientId;
    double heartRate;
    std::cout << "Patient ID: ";
    std::cin >> patientId;
    std::cout << "Heart rate reading: ";
    std::cin >> heartRate;

    // TODO: append "<patientId>,<heartRate>" to vitals_log.csv using std::ios::app.

    // TODO: read the whole file back, printing every entry as
    // "Patient <patientId>: <heartRate> bpm".

    // TODO: count and print how many entries in the whole file fall
    // outside [LOW_HEART_RATE, HIGH_HEART_RATE].

    return 0;
}
