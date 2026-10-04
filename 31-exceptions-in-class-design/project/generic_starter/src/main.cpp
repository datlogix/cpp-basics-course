#include "registrar.h"

#include <iostream>
#include <sstream>

using namespace makersplace::school;

int main() {
    Registrar registrar;
    registrar.addCourse("Robotics 1", 2);
    registrar.addCourse("Robotics 2", 2, "Robotics 1");
    registrar.addCourse("Coding Club", 3);

    // Stands in for a CSV file. Line 3 is corrupted.
    std::istringstream csv("MP-001,Ama Mensah,13\n"
                           "MP-002,Kojo Asante,14\n"
                           "MP-003,Esi Quaye,thirteen\n"
                           "MP-004,Yaw Boateng,12\n");
    try {
        int loaded = registrar.loadStudents(csv);
        std::cout << "Loaded " << loaded << " students" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Loading stopped: " << e.what() << "  <- TODO: one bad line must not stop the rest"
                  << std::endl;
    }

    // TODO: enrol students, triggering every kind of error, with handlers
    // ordered most-specific first; use CourseFullError's data.
    // TODO: show a failed enrolMany() leaves everything unchanged.
    registrar.print();
    return 0;
}
