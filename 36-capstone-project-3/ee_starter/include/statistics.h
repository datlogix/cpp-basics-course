#pragma once

#include <concepts>
#include <vector>

namespace makersplace::energy {

template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// Summary statistics for reports (Stage 3).
template <Numeric T>
class Statistics {
private:
    std::vector<T> values;

public:
    void add(T v) { values.push_back(v); }
    int count() const { return static_cast<int>(values.size()); }
    double mean() const;
    // TODO: min(), max(), standardDeviation()
};

template <Numeric T>
double Statistics<T>::mean() const {
    if (values.empty()) {
        return 0;
    }
    double total = 0;
    for (T v : values) {
        total += v;
    }
    return total / values.size();
}

} // namespace makersplace::energy
