// SINGLETON: exactly one instance, reachable from anywhere.
// Shown so you can recognise it - and then the usually-better alternative:
// create one object in main and PASS it to whoever needs it.
#include <iostream>
#include <string>

class AppConfig {
private:
    std::string schoolName = "Unnamed school";
    int termNumber = 1;

    AppConfig() { std::cout << "  (AppConfig created)" << std::endl; } // private: nobody else can create one

public:
    static AppConfig& instance() {
        static AppConfig theOne; // created the FIRST time this line runs; lives until the program ends
        return theOne;
    }

    AppConfig(const AppConfig&) = delete;            // no copies
    AppConfig& operator=(const AppConfig&) = delete;

    void setSchoolName(const std::string& n) { schoolName = n; }
    std::string getSchoolName() const { return schoolName; }
    int getTerm() const { return termNumber; }
};

// Any function, anywhere, can reach the singleton - convenient, but this
// hidden dependency is invisible in the function's signature.
void printReportHeader() {
    std::cout << "  " << AppConfig::instance().getSchoolName() << " - Term " << AppConfig::instance().getTerm()
              << " report" << std::endl;
}

// The alternative: the dependency is VISIBLE, and a test could pass a different config.
struct Config {
    std::string schoolName;
    int termNumber;
};

void printReportHeaderExplicit(const Config& config) {
    std::cout << "  " << config.schoolName << " - Term " << config.termNumber << " report" << std::endl;
}

int main() {
    std::cout << "Singleton:" << std::endl;
    AppConfig::instance().setSchoolName("MakersPlace Academy");
    printReportHeader();
    printReportHeader(); // same instance - created only once
    // AppConfig another;  // ERROR: constructor is private

    std::cout << "Passing the dependency instead:" << std::endl;
    Config config{"MakersPlace Academy", 2};
    printReportHeaderExplicit(config);
    return 0;
}
