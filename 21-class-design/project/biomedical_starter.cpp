// Module 21 Project - Track C: Clinic Appointment System, redesigned
// See project/README.md for requirements.
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

const int CURRENT_YEAR = 2026;

class Patient {
private:
    // INVARIANT: name is never empty, and 1900 <= birthYear <= CURRENT_YEAR.
    static int nextFolder;

    const std::string folderNumber;
    std::string name;
    int birthYear = CURRENT_YEAR;
    bool needsDetails = false;

    static std::string makeFolderNumber(); // "CL-0001", "CL-0002", ...

public:
    Patient(std::string n, int year);
    // TODO: make this delegate to Patient(n, CURRENT_YEAR), then set needsDetails = true
    explicit Patient(std::string n) : folderNumber(makeFolderNumber()), name(n) {}

    std::string getFolderNumber() const { return folderNumber; }
    std::string getName() const { return name; }

    int ageInYear(int year) const;          // TODO
    bool completeDetails(int year);         // TODO: validate, clear needsDetails
    void print() const;                     // TODO

    static int patientsRegistered() { return nextFolder - 1; }
};

int Patient::nextFolder = 1;

std::string Patient::makeFolderNumber() {
    std::ostringstream out;
    out << "CL-" << std::setw(4) << std::setfill('0') << nextFolder;
    nextFolder++;
    return out.str();
}

Patient::Patient(std::string n, int year) : folderNumber(makeFolderNumber()), name(n), birthYear(year) {
    // TODO: enforce the invariant (empty name -> "Unknown",
    //       bad year -> CURRENT_YEAR), printing a warning for each fix.
}

int Patient::ageInYear(int year) const {
    // TODO
    (void)year;
    return 0;
}

bool Patient::completeDetails(int year) {
    // TODO: validate the year, store it, clear needsDetails
    (void)year;
    return false;
}

void Patient::print() const {
    // TODO: folder number, name, birth year, and "(details needed)" if needsDetails
}

int main() {
    Patient a("Adwoa Boakye", 1988);
    Patient b("Yaw Darko");        // walk-in, needs details
    Patient c("", 1850);           // invalid - should be corrected with warnings

    // TODO: print all three, complete b's details, print again, and
    //       show Patient::patientsRegistered().

    return 0;
}
