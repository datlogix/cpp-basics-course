#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string name;
    double score;
    std::cout << "Name: ";
    std::cin >> name;
    std::cout << "Score: ";
    std::cin >> score;

    std::ofstream outFile("scores.csv", std::ios::app);
    outFile << name << "," << score << std::endl;
    outFile.close();

    std::ifstream inFile("scores.csv");
    std::string line;
    double sum = 0;
    int count = 0;

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string fileName;
        std::string scoreStr;
        std::getline(ss, fileName, ',');
        std::getline(ss, scoreStr, ',');
        double fileScore = std::stod(scoreStr);

        std::cout << fileName << " scored " << fileScore << std::endl;
        sum += fileScore;
        count++;
    }
    inFile.close();

    if (count > 0) {
        std::cout << "Average score: " << sum / count << std::endl;
    }

    return 0;
}
