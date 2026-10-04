// STATIC vs DYNAMIC (requirement 7): which parts use each, and why?
//
#include "column.h"
#include "rolling_window.h"
#include "statistics.h"

#include <iostream>
#include <string>
#include <vector>

using namespace makersplace::school;

class Student {
private:
    std::string name;
    std::vector<double> scores;

public:
    explicit Student(std::string n) : name(n) {}
    void addScore(double s) { scores.push_back(s); }
    std::string getName() const { return name; }
    double average() const {
        Statistics<double> s;
        for (double x : scores) s.add(x);
        return s.mean();
    }
};

// TODO (requirement 6): concept Gradable, a Team class (no shared base with
// Student), and template <Gradable G> void printRanking(std::vector<G> people)

int main() {
    Statistics<double> maths;
    for (double s : {72.0, 85.0, 64.0, 90.0, 58.0}) {
        maths.add(s);
    }
    std::cout << "Maths: " << maths.count() << " scores, mean " << maths.mean() << std::endl;

    // TODO: Statistics<bool> attendance; ...attendanceRate()
    // TODO: RollingWindow<double, 5> recentForm; push 8 scores, forEach to print
    // TODO: a report table of ReportColumn<std::string>, <double> and <bool> columns
    // TODO: printRanking() with Students AND Teams
    return 0;
}
