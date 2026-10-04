/*
  The diamond problem, and virtual inheritance.

             Device
            /      \
   PoweredDevice   NetworkedDevice
            \      /
            SmartPlug
*/
#include <iostream>
#include <string>

// ---------------- WITHOUT virtual inheritance ----------------
namespace plain {

class Device {
protected:
    std::string serial;

public:
    explicit Device(std::string s) : serial(s) { std::cout << "    [+] Device " << serial << std::endl; }
};

class PoweredDevice : public Device {
public:
    PoweredDevice(std::string s) : Device(s + "-P") {}
    std::string poweredSerial() const { return serial; }
};

class NetworkedDevice : public Device {
public:
    NetworkedDevice(std::string s) : Device(s + "-N") {}
    std::string networkedSerial() const { return serial; }
};

class SmartPlug : public PoweredDevice, public NetworkedDevice {
public:
    explicit SmartPlug(std::string s) : PoweredDevice(s), NetworkedDevice(s) {}
    // std::string getSerial() const { return serial; } // ERROR: ambiguous - which Device?
};

} // namespace plain

// ---------------- WITH virtual inheritance ----------------
namespace fixed {

class Device {
protected:
    std::string serial;

public:
    explicit Device(std::string s) : serial(s) { std::cout << "    [+] Device " << serial << std::endl; }
    std::string getSerial() const { return serial; }
};

class PoweredDevice : virtual public Device { // virtual: share ONE Device
protected:
    int volts;

public:
    PoweredDevice(std::string s, int v) : Device(s), volts(v) {}
};

class NetworkedDevice : virtual public Device { // virtual on BOTH middle classes
protected:
    std::string ipAddress;

public:
    NetworkedDevice(std::string s, std::string ip) : Device(s), ipAddress(ip) {}
};

class SmartPlug : public PoweredDevice, public NetworkedDevice {
public:
    SmartPlug(std::string s, std::string ip)
        : Device(s),                // the MOST-DERIVED class constructs the shared base
          PoweredDevice(s, 230),    // their Device(...) calls are skipped
          NetworkedDevice(s, ip) {}

    void describe() const {
        std::cout << "    SmartPlug " << serial << " at " << volts << " V, IP " << ipAddress << std::endl;
    }
};

} // namespace fixed

int main() {
    std::cout << "Without virtual inheritance:" << std::endl;
    plain::SmartPlug p("SP-01");
    std::cout << "    powered path serial:   " << p.poweredSerial() << std::endl;
    std::cout << "    networked path serial: " << p.networkedSerial() << "  <- a SECOND Device!"
              << std::endl;

    std::cout << "With virtual inheritance:" << std::endl;
    fixed::SmartPlug q("SP-02", "192.168.1.20");
    q.describe();
    std::cout << "    one serial number: " << q.getSerial() << std::endl;
    return 0;
}
