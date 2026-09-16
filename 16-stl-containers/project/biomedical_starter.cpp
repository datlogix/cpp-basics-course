// Module 16 Project - Track C: Patient Database (heart-rate readings by patient)
// See project/README.md for requirements.
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    const double LOW_HEART_RATE = 60.0;
    const double HIGH_HEART_RATE = 100.0;
    std::map<std::string, std::vector<double>> patientReadings;

    int choice;
    do {
        std::cout << std::endl;
        std::cout << "1. Add reading for a patient" << std::endl;
        std::cout << "2. Print patient summaries (count + average)" << std::endl;
        std::cout << "3. Print patients flagged by their most recent reading" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // TODO: read a patient ID and a heart-rate reading, push_back
                // it into patientReadings[patientId].
                break;
            }
            case 2:
                // TODO: for every patient, print their reading count and average heart rate.
                break;
            case 3:
                // TODO: for every patient, check their LAST reading
                // (readings.back()) against [LOW_HEART_RATE, HIGH_HEART_RATE]
                // and print them if it's outside that range.
                break;
            case 4:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid option." << std::endl;
        }
    } while (choice != 4);

    return 0;
}
