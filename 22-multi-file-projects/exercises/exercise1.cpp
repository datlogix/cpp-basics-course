// Exercise 1: Multi-File Projects & Namespaces
//
// This file is a complete, working program - but everything is in one
// file. Your job is to split it into a proper multi-file project.
//
// TODO 1: Create a folder exercises/exercise1/ containing three files:
//           gradebook.h    - the class definition (declarations only, plus
//                            any one-line getters you choose to keep inline)
//                            and the DECLARATION of letterGrade()
//           gradebook.cpp  - every method definition (Gradebook::...) and the
//                            DEFINITION of letterGrade()
//           main.cpp       - only main()
// TODO 2: Protect gradebook.h with #pragma once.
// TODO 3: Put the class AND letterGrade() inside a namespace called school
//         (in both the header and the .cpp file). Update main.cpp to use
//         school::Gradebook - do NOT write "using namespace" in the header.
// TODO 4: Make sure each file includes only what it needs: <string> and
//         <vector> in the header (because members use them), <iostream>
//         only where something is printed.
// TODO 5: Build it with
//           g++ -std=c++17 -Wall -Wextra main.cpp gradebook.cpp -o gradebook
//         and confirm the output is identical to this single-file version.
// TODO 6 (stretch): Add a CMakeLists.txt and build it with CMake too.
//
// To run THIS original version:
//   g++ -std=c++17 -Wall -Wextra exercise1.cpp -o exercise1
//   ./exercise1
#include <iostream>
#include <string>
#include <vector>

std::string letterGrade(double average) {
    if (average >= 80) return "A";
    if (average >= 70) return "B";
    if (average >= 60) return "C";
    if (average >= 50) return "D";
    return "F";
}

class Gradebook {
private:
    std::string subject;
    std::vector<std::string> names;
    std::vector<double> scores;

public:
    explicit Gradebook(std::string s) : subject(s) {}

    bool addResult(std::string name, double score) {
        if (score < 0 || score > 100) {
            return false;
        }
        names.push_back(name);
        scores.push_back(score);
        return true;
    }

    double average() const {
        if (scores.empty()) {
            return 0;
        }
        double total = 0;
        for (double s : scores) {
            total += s;
        }
        return total / scores.size();
    }

    void print() const {
        std::cout << subject << " results:" << std::endl;
        for (size_t i = 0; i < names.size(); i++) {
            std::cout << "  " << names[i] << ": " << scores[i]
                      << " (" << letterGrade(scores[i]) << ")" << std::endl;
        }
        std::cout << "  Class average: " << average()
                  << " (" << letterGrade(average()) << ")" << std::endl;
    }
};

int main() {
    Gradebook maths("Mathematics");
    maths.addResult("Akosua", 84);
    maths.addResult("Kwabena", 67);
    maths.addResult("Selorm", 72);
    maths.addResult("Invalid", 140); // rejected

    maths.print();
    return 0;
}
