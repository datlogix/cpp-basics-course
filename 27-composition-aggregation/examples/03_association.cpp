// ASSOCIATION (two-way): a Doctor knows their Patients, and each Patient
// knows their Doctor. One method updates BOTH sides so they can never
// disagree.
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Doctor; // forward declaration (Module 22) - Patient refers to Doctor

class Patient {
private:
    std::string name;
    Doctor* doctor = nullptr; // non-owning: association

    friend class Doctor; // lets Doctor keep both sides consistent (Module 30 covers friend)

public:
    explicit Patient(std::string n) : name(n) {}
    std::string getName() const { return name; }
    const Doctor* getDoctor() const { return doctor; }
};

class Doctor {
private:
    std::string name;
    std::vector<Patient*> patients; // non-owning: association

public:
    explicit Doctor(std::string n) : name(n) {}
    std::string getName() const { return name; }

    // The ONLY way to change the association. It updates both sides.
    void takeOn(Patient& p) {
        if (p.doctor == this) {
            return;
        }
        if (p.doctor != nullptr) {
            p.doctor->letGo(p); // remove from the previous doctor's list first
        }
        patients.push_back(&p);
        p.doctor = this;
    }

    void letGo(Patient& p) {
        // The "erase-remove idiom" (Module 17): remove() shuffles every
        // matching pointer to the end, erase() then chops them off.
        patients.erase(std::remove(patients.begin(), patients.end(), &p), patients.end());
        if (p.doctor == this) {
            p.doctor = nullptr;
        }
    }

    void printCaseload() const {
        std::cout << "  " << name << ":";
        for (const Patient* p : patients) {
            std::cout << " " << p->getName();
        }
        std::cout << std::endl;
    }
};

void printDoctorOf(const Patient& p) {
    std::cout << "  " << p.getName() << "'s doctor: "
              << (p.getDoctor() != nullptr ? p.getDoctor()->getName() : "none") << std::endl;
}

int main() {
    Doctor asante("Dr Asante");
    Doctor boateng("Dr Boateng");
    Patient esi("Esi");
    Patient kofi("Kofi");

    asante.takeOn(esi);
    asante.takeOn(kofi);
    asante.printCaseload();
    boateng.printCaseload();

    std::cout << "Kofi moves to Dr Boateng:" << std::endl;
    boateng.takeOn(kofi); // both doctors' lists AND Kofi's own pointer are updated
    asante.printCaseload();
    boateng.printCaseload();
    printDoctorOf(esi);
    printDoctorOf(kofi);
    return 0;
}
