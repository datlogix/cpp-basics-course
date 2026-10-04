#include "dose.h"

#include <iostream>
#include <sstream>

using namespace makersplace::clinic;

int main() {
    Dose paracetamol = Dose::mg(500);
    Dose extra = Dose::mcg(250);
    std::cout << "Combined: " << paracetamol + extra << std::endl;

    MedicationChart chart;
    chart[6] = paracetamol;
    chart[12] = paracetamol;
    chart[18] = paracetamol;
    chart[22] = Dose::mg(1000); // too much for a single dose?

    // TODO: daily total, and  2 * paracetamol  /  paracetamol * 2
    // TODO: read doses from std::istringstream("500 mg 250 mcg 3 tablets")
    // TODO: compare doses with <, ==, <=>
    // TODO: count hours above a 750 mg single-dose limit with ExceedsLimit
    // TODO: check the daily total against a 4000 mg daily maximum
    // TODO: show chart[25] throwing std::out_of_range
    return 0;
}
