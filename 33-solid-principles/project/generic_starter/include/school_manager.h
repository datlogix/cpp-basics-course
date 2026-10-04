// WARNING: this class is deliberately badly designed. Refactor it!
#pragma once

#include <iostream>
#include <string>
#include <vector>

class SmsGateway {
public:
    void sendSms(std::string phone, std::string text) {
        std::cout << "    [SMS " << phone << "] " << text << std::endl;
    }
};

struct StudentRecord {
    std::string id;
    std::string name;
    std::string parentPhone;
    std::string scholarship; // "none", "academic", "sports"
    std::vector<std::string> assessmentTypes; // "exam", "test", "homework"
    std::vector<double> marks;
    std::vector<double> outOf;
};

class SchoolManager {
public:
    std::vector<StudentRecord> students; // public data!
    double baseFee = 1500;
    SmsGateway sms;

    void addStudent(std::string id, std::string name, std::string phone, std::string scholarship);
    void addResult(std::string id, std::string type, double mark, double outOf);
    void doEverything();
};
