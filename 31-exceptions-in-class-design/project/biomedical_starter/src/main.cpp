#include "medication_record.h"

#include <iostream>
#include <sstream>

using namespace makersplace::clinic;

int main() {
    MedicationRecord meds;
    meds.setDailyMaximum("Paracetamol", 4000);
    meds.setDailyMaximum("Ibuprofen", 1200);
    meds.setDailyMaximum("Amoxicillin", 3000);
    meds.addPatient("CL-0001", {});
    meds.addPatient("CL-0002", {"Amoxicillin"}); // penicillin allergy

    // Stands in for a CSV file. Line 2 is corrupted.
    std::istringstream csv("CL-0001,Paracetamol,1000,3\n"
                           "CL-0001,Ibuprofen,four hundred,3\n"
                           "CL-0002,Paracetamol,500,4\n");
    try {
        int loaded = meds.loadOrders(csv);
        std::cout << "Loaded " << loaded << " orders" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Loading stopped: " << e.what() << "  <- TODO: one bad line must not stop the rest"
                  << std::endl;
    }

    // TODO: a ward round for CL-0002 prescribing Ibuprofen AND Amoxicillin -
    // show prescribeAll() refusing it (AllergyConflictError) and the record
    // left unchanged; then a round for CL-0001 that would exceed the
    // Paracetamol maximum (DoseLimitError - use its data).
    meds.print();
    return 0;
}
