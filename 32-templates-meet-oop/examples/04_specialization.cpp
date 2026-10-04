// Template specialisation: a custom version for one particular type.
#include <iostream>
#include <string>
#include <vector>

// ----- Function template + full specialisations -----
template <typename T>
std::string describe(const T& value) {
    return "value: " + std::to_string(value);
}

template <>
std::string describe<bool>(const bool& value) {
    return value ? "value: yes" : "value: no";
}

template <>
std::string describe<std::string>(const std::string& value) { // std::to_string can't take a string
    return "value: \"" + value + "\"";
}

// ----- Class template + a full specialisation for bool -----
template <typename T>
class Statistics {
private:
    std::vector<T> values;

public:
    void add(T v) { values.push_back(v); }
    double mean() const {
        double total = 0;
        for (const T& v : values) total += v;
        return values.empty() ? 0 : total / values.size();
    }
};

template <>
class Statistics<bool> { // a completely separate class - it shares nothing with the general one
private:
    int trues = 0;
    int total = 0;

public:
    void add(bool v) {
        total++;
        if (v) {
            trues++;
        }
    }
    double fractionTrue() const { return total == 0 ? 0 : static_cast<double>(trues) / total; }
};

int main() {
    std::cout << describe(42) << std::endl;
    std::cout << describe(3.5) << std::endl;
    std::cout << describe(true) << std::endl;
    std::cout << describe(std::string("Ghana")) << std::endl;

    Statistics<double> temps;
    temps.add(29.0);
    temps.add(31.0);
    std::cout << "mean temperature: " << temps.mean() << std::endl;

    Statistics<bool> doorOpen; // uses the specialisation
    for (bool open : {true, false, false, true, true}) {
        doorOpen.add(open);
    }
    std::cout << "door open " << doorOpen.fractionTrue() * 100 << "% of the time" << std::endl;
    // doorOpen.mean();  // ERROR: Statistics<bool> has no mean() - it's a different class
    return 0;
}
