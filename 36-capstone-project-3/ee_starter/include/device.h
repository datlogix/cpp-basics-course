#pragma once

#include <string>

namespace makersplace::energy {

// The abstract base of the device hierarchy (Stage 2).
// Light, Socket, AirConditioner and Sensor derive from it.
class Device {
protected:
    std::string id;
    std::string room;

public:
    Device(std::string deviceId, std::string roomName); // throws if the ID is empty
    virtual ~Device() = default;

    std::string getId() const { return id; }   // satisfies HasId for Repository<T>
    std::string getRoom() const { return room; }

    virtual std::string kind() const = 0;
    // TODO (Stage 2): more pure virtual behaviour your design needs
};

} // namespace makersplace::energy
