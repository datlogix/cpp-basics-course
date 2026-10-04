// Two objects owning each other with shared_ptr form a CYCLE: neither
// count ever reaches zero, so neither is ever deleted. weak_ptr fixes it.
#include <iostream>
#include <memory>
#include <string>

// ---------- The leaking version ----------
struct LeakyDoctor;

struct LeakyPatient {
    std::string name = "patient (leaky)";
    std::shared_ptr<LeakyDoctor> doctor; // owns the doctor
    ~LeakyPatient() { std::cout << "  [-] " << name << std::endl; }
};

struct LeakyDoctor {
    std::string name = "doctor (leaky)";
    std::shared_ptr<LeakyPatient> patient; // owns the patient -> CYCLE
    ~LeakyDoctor() { std::cout << "  [-] " << name << std::endl; }
};

// ---------- The fixed version ----------
struct Doctor;

struct Patient {
    std::string name = "patient (fixed)";
    std::shared_ptr<Doctor> doctor; // owns the doctor
    ~Patient() { std::cout << "  [-] " << name << std::endl; }
};

struct Doctor {
    std::string name = "doctor (fixed)";
    std::weak_ptr<Patient> patient; // OBSERVES the patient - no ownership, no cycle
    ~Doctor() { std::cout << "  [-] " << name << std::endl; }

    void checkOn() const {
        if (std::shared_ptr<Patient> p = patient.lock()) { // lock(): a shared_ptr, or empty
            std::cout << "  " << name << " checks on " << p->name << std::endl;
        } else {
            std::cout << "  " << name << ": patient record no longer exists" << std::endl;
        }
    }
};

int main() {
    std::cout << "Leaky cycle:" << std::endl;
    {
        std::shared_ptr<LeakyPatient> p = std::make_shared<LeakyPatient>();
        std::shared_ptr<LeakyDoctor> d = std::make_shared<LeakyDoctor>();
        p->doctor = d;
        d->patient = p;
    } // p and d go away, but each object still keeps the other alive
    std::cout << "  (no destructor messages above - both objects leaked!)" << std::endl;

    std::cout << "Fixed with weak_ptr:" << std::endl;
    std::shared_ptr<Doctor> keepDoctor;
    {
        std::shared_ptr<Patient> p = std::make_shared<Patient>();
        std::shared_ptr<Doctor> d = std::make_shared<Doctor>();
        p->doctor = d;
        d->patient = p; // weak: the patient's count stays at 1
        d->checkOn();
        keepDoctor = d;
    } // patient deleted here (its only owner, p, is gone)
    keepDoctor->checkOn();
    std::cout << "end of main" << std::endl;
    return 0;
}
