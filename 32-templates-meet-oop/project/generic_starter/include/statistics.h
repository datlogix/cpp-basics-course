// TODO (requirements): explain here why template code lives in a header,
// not in a .cpp file.
#pragma once

#include <cmath>
#include <concepts>
#include <stdexcept>
#include <vector>

namespace makersplace::school {

// TODO (requirement 2): concept Numeric, and constrain Statistics with it.

template <typename T>
class Statistics {
private:
    std::vector<T> values;

public:
    void add(T v);
    int count() const;
    double mean() const;
    T min() const;               // TODO
    T max() const;               // TODO
    double standardDeviation() const; // TODO
};

template <typename T>
void Statistics<T>::add(T v) {
    values.push_back(v);
}

template <typename T>
int Statistics<T>::count() const {
    return static_cast<int>(values.size());
}

template <typename T>
double Statistics<T>::mean() const {
    if (values.empty()) {
        return 0;
    }
    double total = 0;
    for (const T& v : values) {
        total += v;
    }
    return total / values.size();
}

// TODO: define min(), max(), standardDeviation() here

// TODO (requirement 3): the Statistics<bool> specialisation

} // namespace makersplace::school
