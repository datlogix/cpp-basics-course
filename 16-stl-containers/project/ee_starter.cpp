// Module 16 Project - Track B: Component Inventory (voltage samples by node)
// See project/README.md for requirements.
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    const double OVER_VOLTAGE_THRESHOLD = 4.5;
    std::map<std::string, std::vector<double>> nodeSamples;

    int choice;
    do {
        std::cout << std::endl;
        std::cout << "1. Add sample to a node" << std::endl;
        std::cout << "2. Print node summaries (count + average)" << std::endl;
        std::cout << "3. Print nodes with an over-voltage most-recent sample" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // TODO: read a node name and a voltage sample, push_back
                // it into nodeSamples[node] (creates the entry automatically
                // the first time).
                break;
            }
            case 2:
                // TODO: for every node, print its sample count and average voltage.
                break;
            case 3:
                // TODO: for every node, check its LAST sample
                // (samples.back()) against OVER_VOLTAGE_THRESHOLD and
                // print it if it's exceeded.
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
