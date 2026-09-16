// Module 14 Project - Track B: Sensor Data Logger
// See project/README.md for requirements.
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string timestamp;
    double voltage;
    std::cout << "Timestamp (e.g. 08:00): ";
    std::cin >> timestamp;
    std::cout << "Voltage reading: ";
    std::cin >> voltage;

    // TODO: append "<timestamp>,<voltage>" to sensor_log.csv using std::ios::app.

    // TODO: read the whole file back, printing every entry as
    // "<timestamp> -> <voltage> V".

    // TODO: compute and print min, max, and average voltage across
    // every entry in the file.

    return 0;
}
