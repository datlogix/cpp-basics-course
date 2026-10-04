// An abstract base class that SHARES a procedure (report) but leaves the
// varying steps (read, unit, inSafeRange) as pure virtual functions.
// This is the "Template Method" idea.
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Sensor {
protected:
    std::string name;

public:
    explicit Sensor(std::string n) : name(n) {}
    virtual ~Sensor() {}

    // The SAME reporting procedure for every sensor.
    void report() const {
        double value = read();
        std::cout << "  " << name << ": " << value << " " << unit();
        if (!inSafeRange(value)) {
            std::cout << "  ** OUT OF RANGE **";
        }
        std::cout << std::endl;
    }

protected:
    // The steps that DIFFER - every concrete sensor must supply them.
    virtual double read() const = 0;
    virtual std::string unit() const = 0;
    virtual bool inSafeRange(double value) const = 0;
};

class TemperatureSensor : public Sensor {
private:
    double celsius;

public:
    TemperatureSensor(std::string n, double c) : Sensor(n), celsius(c) {}

protected:
    double read() const override { return celsius; }
    std::string unit() const override { return "C"; }
    bool inSafeRange(double v) const override { return v >= 10 && v <= 35; }
};

class GasSensor : public Sensor {
private:
    double ppm;

public:
    GasSensor(std::string n, double p) : Sensor(n), ppm(p) {}

protected:
    double read() const override { return ppm; }
    std::string unit() const override { return "ppm CO2"; }
    bool inSafeRange(double v) const override { return v < 1000; }
};

// A class that forgets one pure virtual function is STILL abstract:
class HalfFinishedSensor : public Sensor {
public:
    using Sensor::Sensor;

protected:
    double read() const override { return 0; }
    std::string unit() const override { return "?"; }
    // inSafeRange() not overridden
};

int main() {
    // Sensor s("generic");                  // ERROR: Sensor is abstract
    // HalfFinishedSensor h("oops");         // ERROR: still abstract - inSafeRange is missing

    std::vector<std::unique_ptr<Sensor>> lab;
    lab.push_back(std::make_unique<TemperatureSensor>("Lab temperature", 29.5));
    lab.push_back(std::make_unique<TemperatureSensor>("Server cupboard", 41.0));
    lab.push_back(std::make_unique<GasSensor>("Classroom CO2", 1350));

    for (const auto& s : lab) {
        s->report(); // one shared procedure, three different sets of steps
    }
    return 0;
}
