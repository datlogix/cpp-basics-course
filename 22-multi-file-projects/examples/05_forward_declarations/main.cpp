// Two classes that refer to each other, each in its own header, made
// possible by forward declarations.
//
// Build and run (from inside this folder):
//   g++ -std=c++17 -Wall -Wextra main.cpp course.cpp teacher.cpp -o school
//   ./school
#include "course.h"
#include "teacher.h"

int main() {
    Course robotics("Introduction to Robotics");
    Teacher mrsAddo("Mrs Addo");

    robotics.print();
    mrsAddo.assignTo(robotics);

    robotics.print();
    mrsAddo.print();
    return 0;
}
