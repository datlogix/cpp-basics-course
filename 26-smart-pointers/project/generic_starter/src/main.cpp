// OWNERSHIP MAP (Part 4, step 10): for every pointer-like member or
// parameter, say whether it OWNS, SHARES, OBSERVES or BORROWS, and why.
//
#include "club.h"
#include "school.h"

#include <iostream>
#include <memory>

using namespace makersplace::school; // fine in a .cpp file's main - never in a header

int main() {
    School osu("MakersPlace Osu campus");
    School tema("MakersPlace Tema campus");

    osu.hire(std::make_unique<Teacher>("Mr Mensah", 4200, 3));
    osu.hire(std::make_unique<Teacher>("Mrs Addo", 4500, 2));
    osu.hire(std::make_unique<Administrator>("Ms Owusu", 3800));
    osu.printPayroll();

    // TODO (Part 2): transfer Mrs Addo from osu to tema, then print both payrolls.

    std::shared_ptr<Student> ama = osu.enrol("Ama");
    std::shared_ptr<Student> kojo = osu.enrol("Kojo");
    Club robotics("Robotics Club");
    robotics.join(ama);
    robotics.join(kojo);

    // Let go of main's own shared_ptrs, so only the school roll owns the students.
    ama.reset();
    kojo.reset();

    robotics.printRegister();
    osu.studentLeaves("Kojo"); // TODO (Part 3): Kojo should be deleted here...
    robotics.printRegister();  // ...and shown as "(left the school)" here

    std::cout << "end of main:" << std::endl;
    return 0;
}
