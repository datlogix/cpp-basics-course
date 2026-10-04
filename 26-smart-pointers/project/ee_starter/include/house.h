#pragma once

#include "room.h"

#include <memory>
#include <string>
#include <vector>

namespace makersplace::energy {

class House {
private:
    std::vector<std::shared_ptr<Room>> rooms; // OWNS (shares) rooms; smart plugs observe them

public:
    std::shared_ptr<Room> addRoom(std::string name);
    std::shared_ptr<Room> findRoom(std::string name) const;
    void demolish(std::string roomName); // TODO: remove the room's shared_ptr
};

// A monitoring plug that reports on a room without keeping it alive.
class SmartPlug {
private:
    std::weak_ptr<Room> room; // OBSERVES

public:
    explicit SmartPlug(const std::shared_ptr<Room>& r) : room(r) {}
    void report() const; // TODO: lock() the room; print its kWh, or "room no longer exists"
};

} // namespace makersplace::energy
