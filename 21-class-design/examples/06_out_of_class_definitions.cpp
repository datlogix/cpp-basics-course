// Declaring methods inside the class and defining them OUTSIDE it with
// ClassName::methodName. The class body becomes a short "table of
// contents". Module 22 moves these two parts into separate files.
#include <iostream>
#include <string>

class Thermostat {
private:
    std::string location;
    double targetCelsius = 24.0;
    static const int MIN_C = 16;
    static const int MAX_C = 30;

public:
    explicit Thermostat(std::string loc);
    bool setTarget(double celsius);
    double getTarget() const;
    void print() const;
};

// --- definitions ---

Thermostat::Thermostat(std::string loc) : location(loc) {}

bool Thermostat::setTarget(double celsius) {
    if (celsius < MIN_C || celsius > MAX_C) {
        return false;
    }
    targetCelsius = celsius;
    return true;
}

double Thermostat::getTarget() const { // const repeated here
    return targetCelsius;
}

void Thermostat::print() const {
    std::cout << location << " thermostat set to " << targetCelsius << " C" << std::endl;
}

int main() {
    Thermostat lab("Robotics lab");
    lab.print();

    lab.setTarget(22.5);
    lab.print();

    if (!lab.setTarget(45)) {
        std::cout << "45 C refused - outside the safe range" << std::endl;
    }
    lab.print();
    return 0;
}
