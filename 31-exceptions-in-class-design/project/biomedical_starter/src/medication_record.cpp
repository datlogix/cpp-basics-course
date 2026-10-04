#include "medication_record.h"

#include <iostream>
#include <sstream>

namespace makersplace::clinic {

void MedicationRecord::addPatient(const std::string& folder, const std::set<std::string>& allergies) {
    patients[folder] = PatientMeds{folder, allergies, {}};
}

void MedicationRecord::setDailyMaximum(const std::string& drug, double mgPerDay) {
    if (mgPerDay <= 0) {
        throw std::invalid_argument("daily maximum must be positive");
    }
    maxMgPerDay[drug] = mgPerDay;
}

int MedicationRecord::loadOrders(std::istream& csv) {
    int loaded = 0;
    int lineNumber = 0;
    std::string line;
    while (std::getline(csv, line)) {
        lineNumber++;
        std::istringstream fields(line);
        std::string folder, drug, mgText, timesText;
        std::getline(fields, folder, ',');
        std::getline(fields, drug, ',');
        std::getline(fields, mgText, ',');
        std::getline(fields, timesText, ',');

        // TODO: translate std::stod/std::stoi failures into CorruptRecordError
        // (with lineNumber); use prescribe() so every safety check applies;
        // report each problem and carry on with the next line.
        Order o{drug, std::stod(mgText), std::stoi(timesText)};
        patients.at(folder).orders.push_back(o);
        loaded++;
    }
    return loaded;
}

void MedicationRecord::prescribe(const std::string& folder, const Order& order) {
    // TODO: throw PatientNotFoundError, AllergyConflictError, DoseLimitError
    // (include orders the patient ALREADY has for the same drug in the daily
    // total), and only then add the order.
    (void)folder;
    (void)order;
}

void MedicationRecord::prescribeAll(const std::string& folder, const std::vector<Order>& orders) {
    // TODO: STRONG guarantee - validate every order first, then commit.
    (void)folder;
    (void)orders;
}

void MedicationRecord::print() const {
    for (const auto& entry : patients) {
        const PatientMeds& p = entry.second;
        std::cout << "  " << p.folder << ":";
        for (const Order& o : p.orders) {
            std::cout << " " << o.drug << " " << o.mgPerDose << "mg x" << o.dosesPerDay;
        }
        std::cout << std::endl;
    }
}

} // namespace makersplace::clinic
