#include "dose_calculator.h"
#include "prescription_checker.h"

#include <iostream>

using namespace makersplace::clinic;

class ConsolePager : public Pager {
public:
    void page(const std::string& who, const std::string& message) override {
        std::cout << "  [PAGE " << who << "] " << message << std::endl;
    }
};

int main() {
    DoseCalculator paracetamol(15, 1000); // 15 mg/kg, max 1000 mg per dose
    std::cout << "Child, 18 kg: " << paracetamol.doseMg(18) << " mg" << std::endl;
    std::cout << "Adult, 80 kg: " << paracetamol.doseMg(80) << " mg (capped)" << std::endl;

    ConsolePager pager;
    PrescriptionChecker checker(pager);
    checker.setDailyLimit("Paracetamol", 4000);
    checker.check({{"CL-0001", "Paracetamol", 1000, 4}, {"CL-0002", "Paracetamol", 1000, 6}});
    return 0;
}
