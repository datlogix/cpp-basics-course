// Interface Segregation Principle: no class should be forced to implement
// (or depend on) methods it doesn't use.
#include <iostream>
#include <stdexcept>
#include <string>

namespace before {

class SmartDevice { // one FAT interface
public:
    virtual ~SmartDevice() = default;
    virtual void switchOn() = 0;
    virtual void switchOff() = 0;
    virtual void setBrightness(int percent) = 0;
    virtual double readTemperature() = 0;
    virtual void lock() = 0;
};

class SmartBulb : public SmartDevice {
public:
    void switchOn() override { std::cout << "  bulb on" << std::endl; }
    void switchOff() override { std::cout << "  bulb off" << std::endl; }
    void setBrightness(int p) override { std::cout << "  bulb at " << p << "%" << std::endl; }
    double readTemperature() override { throw std::logic_error("a bulb has no thermometer"); } // forced!
    void lock() override { throw std::logic_error("a bulb can't be locked"); }                 // forced!
};

} // namespace before

namespace after {

class Switchable {
public:
    virtual ~Switchable() = default;
    virtual void switchOn() = 0;
    virtual void switchOff() = 0;
};

class Dimmable {
public:
    virtual ~Dimmable() = default;
    virtual void setBrightness(int percent) = 0;
};

class TemperatureSensing {
public:
    virtual ~TemperatureSensing() = default;
    virtual double readTemperature() const = 0;
};

class SmartBulb : public Switchable, public Dimmable { // only what a bulb really does
public:
    void switchOn() override { std::cout << "  bulb on" << std::endl; }
    void switchOff() override { std::cout << "  bulb off" << std::endl; }
    void setBrightness(int p) override { std::cout << "  bulb at " << p << "%" << std::endl; }
};

class Thermostat : public Switchable, public TemperatureSensing {
public:
    void switchOn() override { std::cout << "  thermostat on" << std::endl; }
    void switchOff() override { std::cout << "  thermostat off" << std::endl; }
    double readTemperature() const override { return 26.5; }
};

// Each function depends ONLY on the capability it uses.
void eveningScene(Switchable& light, Dimmable& dimmer) {
    light.switchOn();
    dimmer.setBrightness(40);
}

void climateReport(const TemperatureSensing& sensor) {
    std::cout << "  room temperature " << sensor.readTemperature() << " C" << std::endl;
}

} // namespace after

int main() {
    std::cout << "before:" << std::endl;
    before::SmartBulb oldBulb;
    oldBulb.switchOn();
    try {
        oldBulb.readTemperature();
    } catch (const std::logic_error& e) {
        std::cout << "  error: " << e.what() << std::endl;
    }

    std::cout << "after:" << std::endl;
    after::SmartBulb bulb;
    after::Thermostat thermostat;
    after::eveningScene(bulb, bulb);
    after::climateReport(thermostat);
    // after::climateReport(bulb);  // ERROR: a SmartBulb isn't TemperatureSensing - caught at compile time
    return 0;
}
