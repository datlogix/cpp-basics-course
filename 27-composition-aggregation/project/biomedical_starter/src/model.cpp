#include "model.h"

#include <iostream>

namespace makersplace::clinic {

Patient::Patient(std::string folder, std::string n) : folderNumber(folder), name(n) {}
Patient::~Patient() { std::cout << "  [-] patient " << name << std::endl; }

Bed::Bed(std::string l) : label(l) {}

bool Bed::admit(Patient& p) {
    // TODO: refuse if this bed is occupied; if the patient is already in
    // another bed, release that bed first; then set BOTH sides.
    if (!isFree()) {
        return false;
    }
    occupant = &p;
    return true;
}

void Bed::release() {
    // TODO: also clear the patient's side
    occupant = nullptr;
}

Nurse::Nurse(std::string n) : name(n) {}
Nurse::~Nurse() { std::cout << "  [-] nurse " << name << std::endl; }

} // namespace makersplace::clinic
