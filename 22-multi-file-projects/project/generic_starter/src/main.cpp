// TODO (README step 7): If I change only src/club.cpp, which files does
// CMake recompile, and why?
//
#include "student.h"
// TODO: #include "club.h"

int main() {
    using makersplace::school::Student;

    Student ama("Ama", "JHS 2");
    Student kojo("Kojo");
    ama.print();
    kojo.print();

    // TODO: create clubs and run your Module 20/21 scenario, now using
    // makersplace::school::Club from include/club.h.

    return 0;
}
