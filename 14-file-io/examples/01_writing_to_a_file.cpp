// std::ofstream writes to a file exactly like std::cout writes to the screen.
#include <fstream>
#include <iostream>

int main() {
    std::ofstream outFile("readings.txt");

    if (!outFile) {
        std::cout << "Could not open file for writing." << std::endl;
        return 1;
    }

    outFile << "23.5" << std::endl;
    outFile << "24.1" << std::endl;
    outFile << "22.8" << std::endl;

    outFile.close();
    std::cout << "Wrote readings.txt" << std::endl;

    return 0;
}
