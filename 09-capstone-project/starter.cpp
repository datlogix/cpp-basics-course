// Capstone Project: Student Records & Grading System
// See README.md for the full staged requirements. Build and commit in
// the order the stages appear below - Stage 1, then Stage 2, then Stage 3.
#include <iostream>
#include <string>
#include <vector>

// ---------------------------------------------------------------------
// STAGE 1: Student
// ---------------------------------------------------------------------
class Student {
private:
    std::string name;
    std::vector<double> scores;

public:
    Student(std::string name) {
        // TODO: set this->name; scores starts empty automatically.
    }

    std::string getName() {
        // TODO
        return "";
    }

    void addScore(double score) {
        // TODO: reject scores outside 0-100, otherwise push_back.
    }

    double average() {
        // TODO: guard against dividing by zero when scores is empty.
        return 0;
    }

    std::string letterGrade() {
        // TODO: use average() with if/else if to return "A".."F".
        return "";
    }

    void printReport() {
        // TODO: print name, average, letter grade.
    }
};

// ---------------------------------------------------------------------
// STAGE 2: Classroom
// ---------------------------------------------------------------------
class Classroom {
private:
    std::vector<Student> students;

public:
    void addStudent(std::string name) {
        // TODO: construct a Student and push_back it.
    }

    Student* findStudent(std::string name) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getName() == name) {
                return &students[i]; // & here means "the address of" - a pointer to it
            }
        }
        return nullptr; // nullptr means "no student found"
    }

    void printAllReports() {
        // TODO: call printReport() on every student.
    }

    double classAverage() {
        // TODO
        return 0;
    }

    std::string topStudent() {
        // TODO
        return "";
    }
};

int main() {
    Classroom classroom;

    int choice;
    do {
        std::cout << std::endl;
        std::cout << "1. Add Student" << std::endl;
        std::cout << "2. Add Score to a Student" << std::endl;
        std::cout << "3. Print All Reports" << std::endl;
        std::cout << "4. Show Class Average" << std::endl;
        std::cout << "5. Show Top Student" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                // TODO: read a name, call classroom.addStudent(name)
                break;
            case 2:
                // TODO: read a name and a score. Use findStudent() - remember
                // it can return nullptr if the name doesn't exist (Stage 3:
                // handle that case with a clear message instead of crashing).
                break;
            case 3:
                classroom.printAllReports();
                break;
            case 4:
                // TODO: print classroom.classAverage()
                break;
            case 5:
                // TODO: print classroom.topStudent()
                break;
            case 6:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid option." << std::endl;
        }
    } while (choice != 6);

    return 0;
}
