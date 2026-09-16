// Capstone 2, Track A: Extended Student Records & Grading System
// See README.md for the full staged requirements.
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// ---------------------------------------------------------------------
// STAGE 3 helper (build this alongside Module 18 if you haven't already)
// ---------------------------------------------------------------------
template <typename T>
class Statistics {
private:
    std::vector<T> values;

public:
    void addValue(T v) { values.push_back(v); }

    double mean() const {
        // TODO
        return 0;
    }

    double standardDeviation() const {
        // TODO
        return 0;
    }
};

// ---------------------------------------------------------------------
// STAGE 1: Student hierarchy
// ---------------------------------------------------------------------
class Student {
protected:
    std::string name;
    std::vector<double> scores;

public:
    Student(std::string n) : name(n) {}

    std::string getName() const { return name; }

    void addScore(double score) {
        if (score < 0 || score > 100) {
            throw std::invalid_argument("Score must be between 0 and 100.");
        }
        scores.push_back(score);
    }

    double average() const {
        if (scores.empty()) return 0;
        double sum = 0;
        for (double s : scores) sum += s;
        return sum / scores.size();
    }

    virtual std::string letterGrade() const {
        double avg = average();
        if (avg >= 90) return "A";
        if (avg >= 80) return "B";
        if (avg >= 70) return "C";
        if (avg >= 60) return "D";
        return "F";
    }

    virtual void printReport() const {
        std::cout << name << " (average " << average() << "): " << letterGrade() << std::endl;
    }

    virtual ~Student() {}
};

class UndergraduateStudent : public Student {
public:
    UndergraduateStudent(std::string n) : Student(n) {}
    // Uses Student's default grading scale as-is.
};

class GraduateStudent : public Student {
public:
    GraduateStudent(std::string n) : Student(n) {}

    std::string letterGrade() const override {
        // TODO: a stricter scale, e.g. needs 70+ for a "B" instead of 80+.
        return Student::letterGrade();
    }
};

int main() {
    std::vector<Student*> roster;

    // TODO Stage 1: create a few UndergraduateStudent/GraduateStudent
    // with new, add scores, print every report with one polymorphic loop.

    // TODO Stage 2: persist the roster to a CSV file (std::ios::app),
    // reload it at startup, throw/catch on invalid scores and on
    // looking up a student who doesn't exist, and rebuild the "find by
    // name" logic around a std::map<std::string, Student*>.

    // TODO Stage 3: rank students by average with std::sort, count
    // honor-roll students with std::count_if, and feed every student's
    // average into a Statistics<double> to print the class mean and
    // standard deviation.

    for (Student* s : roster) {
        delete s;
    }

    return 0;
}
