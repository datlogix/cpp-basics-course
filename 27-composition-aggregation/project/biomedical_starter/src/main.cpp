#include "model.h"

#include <iostream>

using namespace makersplace::clinic;

int main() {
    // Part 3 demonstration of the problem: the medical record can be altered.
    VitalsLog temps;
    temps.push_back(37.2);
    temps.push_back(38.9);
    temps[1] = 37.0;  // a recorded fever silently "edited away"!
    temps.push_back(120.0); // and an impossible reading accepted
    std::cout << "VitalsLog has " << temps.size() << " readings, latest " << temps.latest() << std::endl;

    Patient esi("CL-0001", "Esi Badu");
    Bed a1("Ward A bed 1");
    Bed b2("Ward B bed 2");

    a1.admit(esi);
    std::cout << "Esi is in " << (esi.getBed() != nullptr ? esi.getBed()->getLabel() : "no bed")
              << "  <- TODO: Bed::admit must update the patient's side too" << std::endl;

    // TODO (Part 4): finish the scenario from the README - wards of beds in a
    // hospital, admissions, a transfer to the other ward (both sides
    // updated!), handover reports, and disbanding a care team to show the
    // nurses survive.
    (void)b2;

    std::cout << "end of main:" << std::endl;
    return 0;
}
