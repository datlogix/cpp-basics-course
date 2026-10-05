// C++ Foundations Project Book - Chapter 6, Activity 3: Refactor the Grade Tracker
// Difficulty: CHALLENGE
//
// Use only: everything from Modules 1-5, plus your own functions with
// parameters and return values, void functions, and prototypes.
// Parameters are passed by value.
// Not yet: reference parameters (&), default parameters, overloading or
// recursion (Module 7).
//
// Refactoring means improving a program's STRUCTURE without changing what
// it does. Start from YOUR OWN Module 5 project
// (05-data-structures/project/starter.cpp).
//
// Compile and run (from this folder):
//     g++ grade_tracker_refactor.cpp -o grade_tracker_refactor
//     ./grade_tracker_refactor

// TODO 1: Run your Module 5 project and paste its output into this comment.
//         This is the behaviour your refactored program must keep:
//
//         (paste output here)

#include <iostream>
#include <string>
#include <vector>

// The struct must come BEFORE any prototype that uses it.
struct Student {
    std::string name;
    std::vector<double> scores;
};

// Prototypes - definitions are below main.
double average(std::vector<double> scores);
double classAverage(std::vector<Student> students);
std::string topStudentName(std::vector<Student> students);
void printStudent(Student s);

int main() {
    std::vector<Student> classroom;

    // TODO 2: Copy the code from your Module 5 main that fills classroom
    //         with students and scores.

    // TODO 3: Replace the rest of your old main with calls to the
    //         functions below, so main can be read at a glance.

    // TODO 4: Run it, check the output is IDENTICAL to TODO 1, and write
    //         one advantage of the new version in a comment.

    return 0;
}

// TODO 2-3: Move the work from your old main into these functions.
double average(std::vector<double> scores) {
    return 0;
}

double classAverage(std::vector<Student> students) {
    return 0;
}

std::string topStudentName(std::vector<Student> students) {
    return "";
}

void printStudent(Student s) {
}
