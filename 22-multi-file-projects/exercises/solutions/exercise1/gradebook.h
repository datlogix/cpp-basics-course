#pragma once

#include <string>
#include <vector>

namespace school {

std::string letterGrade(double average); // declaration only

class Gradebook {
private:
    std::string subject;
    std::vector<std::string> names;
    std::vector<double> scores;

public:
    explicit Gradebook(std::string s);
    bool addResult(std::string name, double score);
    double average() const;
    void print() const;
};

} // namespace school
