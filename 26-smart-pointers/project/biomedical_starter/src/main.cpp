// OWNERSHIP MAP (Part 4, step 10): for every pointer-like member or
// parameter, say whether it OWNS, SHARES, OBSERVES or BORROWS, and why.
//
#include "ward.h"

#include <iostream>
#include <memory>

using namespace makersplace::clinic; // fine in a .cpp file's main - never in a header

int main() {
    Ward medical("Medical Ward");
    Ward emergency("Emergency");

    medical.receive(std::make_unique<Thermometer>("TH-101", 38.6));
    medical.receive(std::make_unique<PulseOximeter>("PO-201", 95, 88));
    medical.receive(std::make_unique<InfusionPump>("IP-301", 100, 60));

    std::shared_ptr<Patient> esi = medical.admit("CL-0001", "Esi Badu");
    std::shared_ptr<Patient> yaw = medical.admit("CL-0002", "Yaw Darko");
    medical.findDevice("TH-101")->attach(esi);
    medical.findDevice("PO-201")->attach(yaw);
    medical.findDevice("IP-301")->attach(esi);
    esi.reset(); // only the ward's admission list owns the patients now
    yaw.reset();

    medical.printDashboard();

    // TODO (Part 2): lend PO-201 from medical to emergency, then print both dashboards.

    medical.discharge("CL-0001"); // TODO (Part 3): Esi should be deleted here...
    medical.printDashboard();     // ...and her devices should say "detach device"

    std::cout << "end of main:" << std::endl;
    return 0;
}
