// A simple CSV pattern: write comma-separated fields, then split them
// back apart with stringstream + getline using ',' as the delimiter.
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::ofstream outFile("log.csv");
    outFile << "08:00,23.5,1.2" << std::endl;
    outFile << "09:00,24.1,1.3" << std::endl;
    outFile.close();

    std::ifstream inFile("log.csv");
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string field;
        while (std::getline(ss, field, ',')) {
            std::cout << field << " | ";
        }
        std::cout << std::endl;
    }
    inFile.close();

    return 0;
}
