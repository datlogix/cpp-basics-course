// C++ Foundations Project Book - Extended Capstone: The Complete School Report System
//
// Uses ONLY Part 1 concepts - you don't need anything from Part 2.
//
// HOW TO START: this file is a skeleton, not a solution. Copy the working
// code from YOUR OWN Module 9 capstone into the classes below as you go,
// then extend it one stage at a time. Finish, test and COMMIT each stage
// before you start the next:
//     git add project-book/extended-capstone
//     git commit -m "Extended capstone stage 1: Subject class"
//     git push
//
// Compile and run (from this folder):
//     g++ school_reports.cpp -o school_reports
//     ./school_reports
#include <iostream>
#include <string>
#include <vector>

// ---------------------------------------------------------------------
// STAGE 1: Subject - the score rules move in here from Student.
// ---------------------------------------------------------------------
class Subject {
private:
    std::string name;
    std::vector<double> scores;

public:
    Subject(std::string name) {
        this->name = name;
    }

    std::string getName() {
        return name;
    }

    // TODO: reject scores outside 0-100 with a clear message.
    void addScore(double score) {
    }

    // TODO: return 0 when there are no scores yet.
    double average() {
        return 0;
    }

    // TODO: "A" (90+), "B" (80+), "C" (70+), "D" (60+), otherwise "F".
    std::string letterGrade() {
        return "";
    }
};

// ---------------------------------------------------------------------
// STAGES 1-2: Student - now holds several Subjects, plus attendance.
// ---------------------------------------------------------------------
class Student {
private:
    std::string name;
    std::vector<Subject> subjects;
    int daysPresent;
    int schoolDays;

public:
    Student(std::string name) {
        this->name = name;
        daysPresent = 0;
        schoolDays = 0;
    }

    std::string getName() {
        return name;
    }

    // STAGE 1 TODO: refuse a subject the student already has.
    void addSubject(std::string subjectName) {
    }

    // STAGE 1 TODO: find the subject by name and add the score to it.
    //               Print a clear message if the subject doesn't exist.
    void addScore(std::string subjectName, double score) {
    }

    // STAGE 1 TODO: the average of the subject averages (0 if no subjects).
    double overallAverage() {
        return 0;
    }

    // STAGE 2 TODO: attendance. attendancePercentage() must never divide
    //               by zero.
    void markPresent() {
    }

    void markAbsent() {
    }

    double attendancePercentage() {
        return 0;
    }

    void printReport() {
        // TODO: name, each subject's average and grade, overall average,
        //       attendance percentage.
    }
};

// ---------------------------------------------------------------------
// Classroom - bring in your Module 9 Classroom and extend it.
// ---------------------------------------------------------------------
class Classroom {
private:
    std::vector<Student> students;

public:
    // STAGE 3 TODO: refuse a name that is already taken.
    void addStudent(std::string name) {
    }

    // Returns a pointer to the student, or nullptr if not found - the same
    // pattern as your Module 9 capstone.
    Student* findStudent(std::string name) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getName() == name) {
                return &students[i];
            }
        }
        return nullptr;
    }

    // STAGE 2 TODO: ask "Present? (y/n)" for each student in turn.
    void takeRegister() {
    }

    // STAGE 4 TODO: each report reads the data but never changes it.
    void reportRanking() {
        // every student by overall average, highest first (your own sort)
    }

    void reportTopPerSubject() {
        // the top student in each subject
    }

    void reportGradeCounts(std::string subjectName) {
        // how many students earned A, B, C, D and F in this subject
    }

    void reportLowAttendance() {
        // every student whose attendance is below 80%
    }
};

// STAGE 3 TODO: keep asking until the user types a number between lowest
//               and highest. Use this for EVERY menu in the program.
//               (You may assume the user types a number.)
int readMenuChoice(int lowest, int highest) {
    int choice = lowest;
    return choice;
}

int main() {
    Classroom classroom;

    // TODO: your Module 9 menu loop, extended with: Add Subject, Take
    //       Register, and a Reports menu (Stage 4).
    // STAGE 5: write REFLECTION.md in this folder.

    return 0;
}
