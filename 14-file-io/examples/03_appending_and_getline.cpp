// std::ios::app appends instead of overwriting. getline reads a whole
// line at a time, from a file exactly as from std::cin.
#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ofstream logFile("session_log.txt", std::ios::app);
    logFile << "Session started." << std::endl;
    logFile.close();

    std::ifstream inFile("session_log.txt");
    std::string line;
    int lineNumber = 1;
    while (std::getline(inFile, line)) {
        std::cout << lineNumber << ": " << line << std::endl;
        lineNumber++;
    }
    inFile.close();

    return 0;
}
