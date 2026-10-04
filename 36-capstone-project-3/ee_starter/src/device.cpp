#include "device.h"

#include <stdexcept>

namespace makersplace::energy {

Device::Device(std::string deviceId, std::string roomName) : id(deviceId), room(roomName) {
    if (id.empty()) {
        throw std::invalid_argument("a device needs an ID");
    }
}

} // namespace makersplace::energy
