#pragma once

#include <string>

namespace makersplace::school {

class ScoreSheet {
private:
    std::string label;
    double* scores;
    int capacity;
    int count = 0;

public:
    static int copies;
    static int moves;

    ScoreSheet(std::string l, int cap);
    ScoreSheet(const ScoreSheet& other);
    ScoreSheet& operator=(const ScoreSheet& other);

    // TODO (Part 1): declare the move constructor and move assignment (noexcept)

    ~ScoreSheet();

    bool add(double score);
    double average() const;
    int size() const { return count; }
    std::string getLabel() const { return label; }
    void print() const;
};

} // namespace makersplace::school
