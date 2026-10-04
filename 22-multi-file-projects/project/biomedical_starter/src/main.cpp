// TODO (README step 7): If I change only src/doctor.cpp, which files does
// CMake recompile, and why?
//
#include "patient.h"
// TODO: #include "doctor.h"

int main() {
    using makersplace::clinic::Patient;

    Patient adwoa("Adwoa Boakye", 1988);
    Patient yaw("Yaw Darko");
    adwoa.print();
    yaw.print();

    // TODO: create Doctors (from include/doctor.h), book appointments
    // (including a refused double-booking), and print each schedule.

    return 0;
}
