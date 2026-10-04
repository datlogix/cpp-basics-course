#pragma once

#include "errors.h"

#include <istream>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace makersplace::clinic {

struct Order {
    std::string drug;
    double mgPerDose;
    int dosesPerDay;
};

struct PatientMeds {
    std::string folder;
    std::set<std::string> allergies;
    std::vector<Order> orders;
};

class MedicationRecord {
private:
    std::map<std::string, PatientMeds> patients;
    std::map<std::string, double> maxMgPerDay; // drug -> daily maximum

public:
    // GUARANTEE: ...
    void addPatient(const std::string& folder, const std::set<std::string>& allergies);

    // GUARANTEE: ...
    void setDailyMaximum(const std::string& drug, double mgPerDay);

    // GUARANTEE: ...
    int loadOrders(std::istream& csv); // TODO: translate errors

    // GUARANTEE: ...
    void prescribe(const std::string& folder, const Order& order); // TODO

    // GUARANTEE: strong
    void prescribeAll(const std::string& folder, const std::vector<Order>& orders); // TODO

    // GUARANTEE: ...
    void print() const;
};

} // namespace makersplace::clinic
