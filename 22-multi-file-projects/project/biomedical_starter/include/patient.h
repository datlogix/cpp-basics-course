// include/patient.h - MODEL CLASS: study this, then split Doctor the same way.
#pragma once

#include <string>

namespace makersplace::clinic {

class Patient {
private:
    // INVARIANT: name is never empty, and 1900 <= birthYear <= CURRENT_YEAR.
    static int nextFolder;

    const std::string folderNumber;
    std::string name;
    int birthYear;
    bool needsDetails = false;

    static std::string makeFolderNumber();

public:
    static const int CURRENT_YEAR = 2026;

    Patient(std::string n, int year);
    explicit Patient(std::string n);

    std::string getFolderNumber() const { return folderNumber; }
    std::string getName() const { return name; }

    int ageInYear(int year) const;
    bool completeDetails(int year);
    void print() const;

    static int patientsRegistered() { return nextFolder - 1; }
};

} // namespace makersplace::clinic
