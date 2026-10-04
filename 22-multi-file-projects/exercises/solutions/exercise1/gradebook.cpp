#include "gradebook.h"

#include <iostream>

namespace school {

std::string letterGrade(double average) {
    if (average >= 80) return "A";
    if (average >= 70) return "B";
    if (average >= 60) return "C";
    if (average >= 50) return "D";
    return "F";
}

Gradebook::Gradebook(std::string s) : subject(s) {}

bool Gradebook::addResult(std::string name, double score) {
    if (score < 0 || score > 100) {
        return false;
    }
    names.push_back(name);
    scores.push_back(score);
    return true;
}

double Gradebook::average() const {
    if (scores.empty()) {
        return 0;
    }
    double total = 0;
    for (double s : scores) {
        total += s;
    }
    return total / scores.size();
}

void Gradebook::print() const {
    std::cout << subject << " results:" << std::endl;
    for (size_t i = 0; i < names.size(); i++) {
        std::cout << "  " << names[i] << ": " << scores[i]
                  << " (" << letterGrade(scores[i]) << ")" << std::endl;
    }
    std::cout << "  Class average: " << average()
              << " (" << letterGrade(average()) << ")" << std::endl;
}

} // namespace school
