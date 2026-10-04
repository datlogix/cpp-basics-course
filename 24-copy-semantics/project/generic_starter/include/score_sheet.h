#pragma once

#include <string>

namespace makersplace::school {

// Owns a raw heap array on purpose, to practise the Rule of Three.
class ScoreSheet {
private:
    std::string label;
    double* scores;
    int capacity;
    int count = 0;

public:
    ScoreSheet(std::string l, int cap);

    // TODO (Part 1): declare the copy constructor
    // TODO (Part 1): declare the copy assignment operator

    ~ScoreSheet();

    bool add(double score);
    void addBonus(double marks); // capped at 100
    double average() const;
    double passRate() const;     // percentage of scores >= 50
    void print() const;
};

} // namespace makersplace::school
