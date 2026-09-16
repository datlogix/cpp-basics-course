// std::ifstream reads from a file. Run 01_writing_to_a_file.cpp first
// so readings.txt exists.
#include <fstream>
#include <iostream>

int main() {
    std::ifstream inFile("readings.txt");

    if (!inFile) {
        std::cout << "Could not open file for reading. Run the writing example first." << std::endl;
        return 1;
    }

    double reading;
    double sum = 0;
    int count = 0;

    while (inFile >> reading) {
        std::cout << "Read: " << reading << std::endl;
        sum += reading;
        count++;
    }

    inFile.close();

    if (count > 0) {
        std::cout << "Average: " << sum / count << std::endl;
    }

    return 0;
}
