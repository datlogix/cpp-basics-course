#include "score_sheet.h"

#include <iostream>

namespace makersplace::school {

ScoreSheet::ScoreSheet(std::string l, int cap)
    : label(l), scores(new double[cap]), capacity(cap) {}

// TODO (Part 1): define the copy constructor (deep copy, print "[copy] ...")
// TODO (Part 1): define the copy assignment operator (print "[assign] ...")

ScoreSheet::~ScoreSheet() {
    std::cout << "  [free] " << label << std::endl;
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

void ScoreSheet::addBonus(double marks) {
    for (int i = 0; i < count; i++) {
        scores[i] += marks;
        if (scores[i] > 100) {
            scores[i] = 100;
        }
    }
    label += " (+" + std::to_string(static_cast<int>(marks)) + " bonus)";
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

double ScoreSheet::passRate() const {
    if (count == 0) {
        return 0;
    }
    int passed = 0;
    for (int i = 0; i < count; i++) {
        if (scores[i] >= 50) {
            passed++;
        }
    }
    return 100.0 * passed / count;
}

void ScoreSheet::print() const {
    std::cout << label << ": average " << average() << ", pass rate " << passRate() << "%"
              << std::endl;
}

} // namespace makersplace::school
