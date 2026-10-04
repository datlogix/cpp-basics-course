#include "model.h"

#include <iostream>

using namespace makersplace::school;

int main() {
    // Part 3 demonstration of the problem: nothing stops invalid scores.
    Gradebook g;
    g.push_back(85);
    g.push_back(250); // should be impossible
    std::cout << "Gradebook average (with an impossible score): " << g.average() << std::endl;

    Student ama("Ama"), kojo("Kojo"), esi("Esi"), yaw("Yaw"), akua("Akua");
    Teacher mensah("Mr Mensah"), addo("Mrs Addo");

    Course robotics("Robotics");
    Course coding("Coding");
    robotics.enrol(ama);
    robotics.enrol(kojo);
    coding.enrol(esi);
    coding.enrol(ama);

    mensah.assign(robotics);
    mensah.assign(coding);
    robotics.printRegister();
    coding.printRegister();

    // TODO (Part 4): finish the scenario from the README - classrooms and a
    // school, a third course, reassign a course to Mrs Addo, a
    // ReportCardPrinter, and destroy a course to show the students survive.
    (void)yaw;
    (void)akua;
    (void)addo;

    std::cout << "end of main:" << std::endl;
    return 0;
}
