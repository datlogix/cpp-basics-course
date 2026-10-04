// VTABLE DIAGRAM (requirement 7): draw the vtable of one concrete class.
//
#include "assessment.h"

#include <iostream>
#include <memory>
#include <vector>

using namespace makersplace::school;

void printReportCard(const std::vector<const Reportable*>& lines) {
    // TODO: print every line - this function must not mention any concrete class
    for (const Reportable* r : lines) {
        std::cout << "  " << r->reportLine() << std::endl;
    }
}

double weightedAverage(const std::vector<const Gradable*>& items) {
    // TODO: requirement 4 - but weight() lives on Assessment, not Gradable.
    // Decide how to handle that WITHOUT naming a concrete class (hint: should
    // Gradable have a weight() too?), and explain your choice in a comment.
    double total = 0;
    for (const Gradable* g : items) {
        total += g->percentage();
    }
    return items.empty() ? 0 : total / items.size();
}

int main() {
    std::vector<std::unique_ptr<Assessment>> akuaResults;
    akuaResults.push_back(std::make_unique<Exam>("End of term exam", 54, 80));
    // TODO: add a Coursework and a RoboticsProject

    std::vector<const Reportable*> card;
    std::vector<const Gradable*> grades;
    for (const auto& a : akuaResults) {
        card.push_back(a.get());
        grades.push_back(a.get());
    }
    // TODO: add an Attendance record to the card (it is Reportable, not Gradable)

    std::cout << "Report card for Akua:" << std::endl;
    printReportCard(card);
    std::cout << "  Average: " << weightedAverage(grades) << "%" << std::endl;

    // TODO (requirement 5): clone the exam for a resit, change the copy's
    // marks, and print both lines.
    return 0;
}
