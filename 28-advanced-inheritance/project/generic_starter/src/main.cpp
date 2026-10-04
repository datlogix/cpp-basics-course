#include "people.h"

#include <iostream>
#include <memory>
#include <vector>

using namespace makersplace::school;

void teachingDuty(Teacher& t) { t.assign("Robotics 101"); }
void researchDuty(Researcher& r) { r.publish("Teaching robotics in Ghanaian JHS classrooms"); }

int main() {
    std::vector<std::unique_ptr<Person>> staff;
    staff.push_back(std::make_unique<Teacher>("T-001", "Mr Mensah", 4200));
    staff.push_back(std::make_unique<Researcher>("R-001", "Dr Osei", 120000));
    // TODO: add a TeachingResearcher and a Principal

    for (const auto& p : staff) {
        p->idCard();
        std::cout << "  monthly pay: GHS " << p->monthlySalaryGhs() << std::endl;
    }

    // TODO (req 2): create a TeachingResearcher and pass it to BOTH
    // teachingDuty() and researchDuty().
    (void)teachingDuty;
    (void)researchDuty;

    // TODO (req 6): show (in a comment) a line that would slice, and the
    // correct alternative.
    return 0;
}
