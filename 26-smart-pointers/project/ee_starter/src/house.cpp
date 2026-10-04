#include "house.h"

#include <iostream>

namespace makersplace::energy {

std::shared_ptr<Room> House::addRoom(std::string name) {
    std::shared_ptr<Room> r = std::make_shared<Room>(name);
    rooms.push_back(r);
    return r;
}

std::shared_ptr<Room> House::findRoom(std::string name) const {
    for (const std::shared_ptr<Room>& r : rooms) {
        if (r->getName() == name) {
            return r;
        }
    }
    return nullptr;
}

void House::demolish(std::string roomName) {
    // TODO
    (void)roomName;
}

void SmartPlug::report() const {
    // TODO
    std::cout << "  smart plug: (not implemented yet)" << std::endl;
}

} // namespace makersplace::energy
