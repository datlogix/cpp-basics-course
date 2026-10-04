// std::shared_ptr: several owners, a reference count, and the object is
// deleted when the LAST owner lets go.
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Patient {
private:
    std::string name;

public:
    explicit Patient(std::string n) : name(n) { std::cout << "  [+] " << name << std::endl; }
    ~Patient() { std::cout << "  [-] " << name << " record released" << std::endl; }
    std::string getName() const { return name; }
};

int main() {
    std::shared_ptr<Patient> admission = std::make_shared<Patient>("Esi Badu");
    std::cout << "after admission: count = " << admission.use_count() << std::endl;

    std::vector<std::shared_ptr<Patient>> wardList;
    std::vector<std::shared_ptr<Patient>> doctorCaseload;

    wardList.push_back(admission);        // copying a shared_ptr: count goes up
    doctorCaseload.push_back(admission);
    std::cout << "on ward list and caseload: count = " << admission.use_count() << std::endl;

    {
        std::shared_ptr<Patient> labOrder = admission;
        std::cout << "lab order placed: count = " << admission.use_count() << std::endl;
    } // labOrder destroyed: count goes down
    std::cout << "lab order complete: count = " << admission.use_count() << std::endl;

    admission.reset();                    // admission desk lets go
    std::cout << "admission desk released it: count = " << wardList[0].use_count() << std::endl;

    wardList.clear();                     // discharged from the ward
    std::cout << "discharged from ward: count = " << doctorCaseload[0].use_count() << std::endl;

    std::cout << "doctor closes the case:" << std::endl;
    doctorCaseload.clear();               // last owner gone -> Patient deleted HERE

    std::cout << "end of main" << std::endl;
    return 0;
}
