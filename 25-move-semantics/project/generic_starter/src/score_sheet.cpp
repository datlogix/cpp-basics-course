#include "score_sheet.h"

#include <iostream>

namespace makersplace::school {

int ScoreSheet::copies = 0;
int ScoreSheet::moves = 0;

ScoreSheet::ScoreSheet(std::string l, int cap) : label(l), scores(new double[cap]), capacity(cap) {}

ScoreSheet::ScoreSheet(const ScoreSheet& other)
    : label(other.label), scores(new double[other.capacity]), capacity(other.capacity),
      count(other.count) {
    for (int i = 0; i < count; i++) {
        scores[i] = other.scores[i];
    }
    copies++;
}

ScoreSheet& ScoreSheet::operator=(const ScoreSheet& other) {
    if (this != &other) {
        double* newScores = new double[other.capacity];
        for (int i = 0; i < other.count; i++) {
            newScores[i] = other.scores[i];
        }
        delete[] scores;
        scores = newScores;
        label = other.label;
        capacity = other.capacity;
        count = other.count;
        copies++;
    }
    return *this;
}

// TODO (Part 1): define the move constructor and move assignment here.
// Leave the source with scores == nullptr, capacity 0, count 0, and
// increment moves.

ScoreSheet::~ScoreSheet() {
    delete[] scores;
}

bool ScoreSheet::add(double score) {
    if (count >= capacity || score < 0 || score > 100) {
        return false;
    }
    scores[count] = score;
    count++;
    return true;
}

double ScoreSheet::average() const {
    if (count == 0) {
        return 0;
    }
    double total = 0;
    for (int i = 0; i < count; i++) {
        total += scores[i];
    }
    return total / count;
}

void ScoreSheet::print() const {
    std::cout << label << ": " << count << " scores, average " << average() << std::endl;
}

} // namespace makersplace::school
