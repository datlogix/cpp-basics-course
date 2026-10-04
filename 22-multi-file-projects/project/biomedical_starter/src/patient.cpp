// src/patient.cpp - MODEL CLASS definitions.
#include "patient.h"

#include <iomanip>
#include <iostream>
#include <sstream>

namespace makersplace::clinic {

int Patient::nextFolder = 1;

std::string Patient::makeFolderNumber() {
    std::ostringstream out;
    out << "CL-" << std::setw(4) << std::setfill('0') << nextFolder;
    nextFolder++;
    return out.str();
}

Patient::Patient(std::string n, int year)
    : folderNumber(makeFolderNumber()), name(n), birthYear(year) {
    if (name.empty()) {
        std::cout << "Warning: empty name, using \"Unknown\"" << std::endl;
        name = "Unknown";
    }
    if (birthYear < 1900 || birthYear > CURRENT_YEAR) {
        std::cout << "Warning: invalid birth year " << year << std::endl;
        birthYear = CURRENT_YEAR;
        needsDetails = true;
    }
}

Patient::Patient(std::string n) : Patient(n, CURRENT_YEAR) {
    needsDetails = true;
}

int Patient::ageInYear(int year) const {
    return year - birthYear;
}

bool Patient::completeDetails(int year) {
    if (year < 1900 || year > CURRENT_YEAR) {
        return false;
    }
    birthYear = year;
    needsDetails = false;
    return true;
}

void Patient::print() const {
    std::cout << folderNumber << " " << name << ", born " << birthYear
              << (needsDetails ? " (details needed)" : "") << std::endl;
}

} // namespace makersplace::clinic
