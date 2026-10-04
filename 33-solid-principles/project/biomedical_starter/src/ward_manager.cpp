#include "ward_manager.h"

void WardManager::admit(std::string bed, std::string name) {
    PatientRecord p;
    p.bed = bed;
    p.name = name;
    patients.push_back(p);
}

void WardManager::record(std::string bed, std::string type, double value) {
    for (int i = 0; i < (int)patients.size(); i++) {
        if (patients[i].bed == bed) {
            patients[i].vitalTypes.push_back(type);
            patients[i].values.push_back(value);
        }
    }
}

// Scores every vital, totals an early warning score, prints the handover, and pages staff.
void WardManager::doShift() {
    std::cout << "SHIFT HANDOVER - " << wardName << std::endl;
    for (int i = 0; i < (int)patients.size(); i++) {
        PatientRecord& p = patients[i];
        int total = 0;
        std::string worst = "";
        int worstScore = 0;
        for (int j = 0; j < (int)p.values.size(); j++) {
            double v = p.values[j];
            int score = 0;
            if (p.vitalTypes[j] == "hr") {
                if (v <= 40 || v >= 131) score = 3;
                else if (v >= 111) score = 2;
                else if (v <= 50 || v >= 91) score = 1;
            } else if (p.vitalTypes[j] == "temp") {
                if (v <= 35.0) score = 3;
                else if (v >= 39.1) score = 2;
                else if (v <= 36.0 || v >= 38.1) score = 1;
            } else if (p.vitalTypes[j] == "spo2") {
                if (v <= 91) score = 3;
                else if (v <= 93) score = 2;
                else if (v <= 95) score = 1;
            } else if (p.vitalTypes[j] == "sbp") {
                if (v <= 90 || v >= 220) score = 3;
                else if (v <= 100) score = 2;
                else if (v <= 110) score = 1;
            }
            total = total + score;
            if (score > worstScore) {
                worstScore = score;
                worst = p.vitalTypes[j];
            }
        }
        std::string risk;
        if (total >= 7) risk = "HIGH";
        else if (total >= 5 || worstScore == 3) risk = "MEDIUM";
        else risk = "LOW";

        std::cout << "  " << p.bed << " " << p.name << ": score " << total << " (" << risk << " risk)";
        if (worst != "") std::cout << ", worst: " << worst;
        std::cout << std::endl;

        if (risk == "HIGH") {
            pager.page("on-call doctor", p.bed + " " + p.name + " needs URGENT review (score " + std::to_string(total) + ")");
        } else if (risk == "MEDIUM") {
            pager.page("nurse in charge", p.bed + " " + p.name + " - increase observations");
        }
    }
}
