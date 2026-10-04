#pragma once

#include <iostream>
#include <string>

namespace makersplace::clinic {

class Patient {
private:
    std::string folderNumber;
    std::string name;

public:
    Patient(std::string folder, std::string n) : folderNumber(folder), name(n) {}
    ~Patient() { std::cout << "  [-] patient " << name << std::endl; }
    std::string getFolderNumber() const { return folderNumber; }
    std::string getName() const { return name; }
};

} // namespace makersplace::clinic
