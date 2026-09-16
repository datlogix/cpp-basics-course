#include <iostream>
#include <string>

class Vehicle {
protected:
    std::string make;
    int topSpeed;

public:
    Vehicle(std::string mk, int speed) {
        make = mk;
        topSpeed = speed;
    }

    void describe() {
        std::cout << make << " - top speed " << topSpeed << " km/h" << std::endl;
    }
};

class ElectricVehicle : public Vehicle {
private:
    double batteryCapacityKwh;

public:
    ElectricVehicle(std::string mk, int speed, double capacity)
        : Vehicle(mk, speed) {
        batteryCapacityKwh = capacity;
    }

    void describe() {
        std::cout << make << " - top speed " << topSpeed << " km/h"
                   << ", battery " << batteryCapacityKwh << " kWh" << std::endl;
    }
};

int main() {
    Vehicle v("Generic Car", 180);
    v.describe();

    ElectricVehicle ev("Electric Sedan", 210, 75.0);
    ev.describe();

    return 0;
}
