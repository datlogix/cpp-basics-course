#include "school_manager.h"

#include <iomanip>

void SchoolManager::addStudent(std::string id, std::string name, std::string phone, std::string scholarship) {
    StudentRecord s;
    s.id = id;
    s.name = name;
    s.parentPhone = phone;
    s.scholarship = scholarship;
    students.push_back(s);
}

void SchoolManager::addResult(std::string id, std::string type, double mark, double outOf) {
    for (int i = 0; i < (int)students.size(); i++) {
        if (students[i].id == id) {
            students[i].assessmentTypes.push_back(type);
            students[i].marks.push_back(mark);
            students[i].outOf.push_back(outOf);
        }
    }
}

// Calculates grades, fees, prints report cards, and texts parents. All at once.
void SchoolManager::doEverything() {
    for (int i = 0; i < (int)students.size(); i++) {
        StudentRecord& s = students[i];
        double weighted = 0;
        double weights = 0;
        for (int j = 0; j < (int)s.marks.size(); j++) {
            double pct = s.marks[j] / s.outOf[j] * 100;
            double w = 0;
            if (s.assessmentTypes[j] == "exam") {
                w = 0.6;
            } else if (s.assessmentTypes[j] == "test") {
                w = 0.25;
            } else if (s.assessmentTypes[j] == "homework") {
                w = 0.15;
            }
            weighted = weighted + pct * w;
            weights = weights + w;
        }
        double avg = 0;
        if (weights > 0) avg = weighted / weights;

        std::string grade;
        if (avg >= 80) grade = "A";
        else if (avg >= 70) grade = "B";
        else if (avg >= 60) grade = "C";
        else if (avg >= 50) grade = "D";
        else grade = "F";

        double fee = baseFee;
        if (s.scholarship == "academic") {
            fee = baseFee * 0.5;
        } else if (s.scholarship == "sports") {
            fee = baseFee - 300;
        }
        if (avg >= 90 && s.scholarship == "none") {
            fee = fee - 100; // merit discount
        }

        std::cout << "REPORT CARD: " << s.name << " (" << s.id << ")" << std::endl;
        std::cout << "  average " << std::fixed << std::setprecision(1) << avg << "%  grade " << grade << std::endl;
        std::cout << "  fees due GHS " << std::setprecision(2) << fee << std::endl;
        if (grade == "F" || grade == "D") {
            sms.sendSms(s.parentPhone, s.name + " needs extra support (grade " + grade + ")");
        }
        if (fee > 1000) {
            sms.sendSms(s.parentPhone, "Fees of GHS " + std::to_string((int)fee) + " are due for " + s.name);
        }
    }
}
