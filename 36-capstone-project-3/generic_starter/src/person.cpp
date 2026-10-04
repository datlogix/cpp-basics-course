#include "person.h"

#include <stdexcept>

namespace makersplace::school {

Person::Person(std::string personId, std::string personName) : id(personId), name(personName) {
    if (id.empty() || name.empty()) {
        throw std::invalid_argument("a person needs an ID and a name");
    }
}

} // namespace makersplace::school
