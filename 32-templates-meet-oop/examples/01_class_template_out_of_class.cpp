// Defining a class template's member functions OUTSIDE the class.
// Every definition repeats "template <typename T>" and uses ClassName<T>::.
// In a multi-file project, ALL of this goes in the header (statistics.h),
// because the compiler needs the full recipe wherever Statistics<X> is used.
#include <iostream>
#include <string>
#include <vector>

template <typename T>
class Statistics {
private:
    std::vector<T> values;

public:
    void add(T v);
    int count() const;
    double mean() const;
    T max() const;
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

template <typename T>
T Statistics<T>::max() const {
    T best = values.at(0); // .at() throws if empty
    for (const T& v : values) {
        if (v > best) {
            best = v;
        }
    }
    return best;
}

int main() {
    Statistics<double> temps;
    temps.add(28.4);
    temps.add(31.2);
    temps.add(29.9);
    std::cout << "temperatures: mean " << temps.mean() << ", max " << temps.max() << std::endl;

    Statistics<int> scores;
    for (int s : {72, 85, 64, 90}) {
        scores.add(s);
    }
    std::cout << "scores: " << scores.count() << " values, mean " << scores.mean() << ", max "
              << scores.max() << std::endl;
    return 0;
}
