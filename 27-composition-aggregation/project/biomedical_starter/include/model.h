// Every class skeleton in one header, to get you started.
// TODO (Part 2): split into one .h/.cpp pair per class.
#pragma once

#include <string>
#include <vector>

namespace makersplace::clinic {

// ---------- Part 3: MISUSED INHERITANCE - fix this ----------
// Temperatures in Celsius. Rules: each reading must be 30-45 C, and
// readings can only be ADDED - never edited or erased (medical record).
class VitalsLog : public std::vector<double> {
public:
    double latest() const { return empty() ? 0 : back(); }
};

class Bed; // forward declaration

class Patient {
private:
    std::string folderNumber;
    std::string name;
    Bed* bed = nullptr; // association (at most one bed)
    // TODO: a VitalsLog member (composition) once Part 3 is done

public:
    Patient(std::string folder, std::string n);
    ~Patient();
    std::string getName() const { return name; }
    const Bed* getBed() const { return bed; }
    // TODO: what does Patient need so that Bed can keep BOTH sides consistent?
};

class Bed {
private:
    std::string label;
    Patient* occupant = nullptr; // association (at most one patient)

public:
    explicit Bed(std::string l);
    std::string getLabel() const { return label; }
    bool isFree() const { return occupant == nullptr; }
    bool admit(Patient& p);  // TODO: the ONE method that updates both sides
    void release();          // TODO: clears both sides
};

class Ward {
    // TODO: name, and its Beds (composition)
};

class Hospital {
    // TODO: name, and its Wards (composition)
};

class Nurse {
private:
    std::string name;

public:
    explicit Nurse(std::string n);
    ~Nurse();
    std::string getName() const { return name; }
};

class CareTeam {
    // TODO: name, and std::vector<Nurse*> (aggregation)
};

class HandoverReport {
    // TODO: void print(const Ward& w) const - a dependency only
};

} // namespace makersplace::clinic
