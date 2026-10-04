#pragma once

#include <concepts>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace makersplace::school {

// Anything with a getId() convertible to std::string can be stored.
template <typename T>
concept HasId = requires(const T& item) {
    { item.getId() } -> std::convertible_to<std::string>;
};

// A generic owning store, keyed by ID (Stage 3).
// It owns its items through unique_ptr, so it also works for abstract
// base classes (e.g. Repository<Person> holding derived objects).
template <HasId T>
class Repository {
private:
    std::vector<std::unique_ptr<T>> items;

public:
    void add(std::unique_ptr<T> item);          // TODO: throw on a duplicate ID
    T* find(const std::string& id) const;        // TODO: nullptr if not found
    std::unique_ptr<T> remove(const std::string& id); // TODO: transfer ownership out
    int size() const { return static_cast<int>(items.size()); }

    // Lets callers loop over every item without owning them.
    template <typename F>
    void forEach(F f) const {
        for (const auto& item : items) {
            f(*item);
        }
    }
};

template <HasId T>
void Repository<T>::add(std::unique_ptr<T> item) {
    // TODO: reject duplicates
    items.push_back(std::move(item));
}

template <HasId T>
T* Repository<T>::find(const std::string& id) const {
    // TODO
    (void)id;
    return nullptr;
}

template <HasId T>
std::unique_ptr<T> Repository<T>::remove(const std::string& id) {
    // TODO
    (void)id;
    return nullptr;
}

} // namespace makersplace::school
