// std::set stores unique values, automatically rejecting duplicates.
#include <iostream>
#include <set>
#include <string>

int main() {
    std::set<std::string> uniquePatientIds;
    uniquePatientIds.insert("P001");
    uniquePatientIds.insert("P002");
    uniquePatientIds.insert("P001"); // duplicate, silently ignored

    std::cout << "Unique patients: " << uniquePatientIds.size() << std::endl; // 2

    for (const std::string& id : uniquePatientIds) {
        std::cout << id << std::endl;
    }

    return 0;
}
