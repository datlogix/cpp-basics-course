// Member function templates: a template method inside a class -
// in an ordinary class, and inside a class template.
#include <array>
#include <iostream>
#include <set>
#include <string>
#include <vector>

class Logger {
private:
    int entries = 0;

public:
    template <typename T>
    void log(const std::string& label, const T& value) {
        entries++;
        std::cout << "  [" << entries << "] " << label << ": " << value << std::endl;
    }
};

template <typename T>
class Statistics {
private:
    std::vector<T> values;

public:
    void add(T v) { values.push_back(v); }

    // Accepts ANY container whose elements can be added: vector, set, array...
    template <typename Container>
    void addAll(const Container& items) {
        for (const auto& item : items) {
            add(item);
        }
    }

    double mean() const {
        double total = 0;
        for (const T& v : values) total += v;
        return values.empty() ? 0 : total / values.size();
    }
    int count() const { return static_cast<int>(values.size()); }
};

int main() {
    Logger log;
    log.log("temperature", 28.4);
    log.log("student", std::string("Ama"));
    log.log("robots built", 12);

    Statistics<double> s;
    std::vector<double> week1 = {28.1, 29.4, 30.0};
    std::set<double> week2 = {27.5, 31.2};
    std::array<double, 2> week3 = {29.9, 30.3};
    s.addAll(week1);
    s.addAll(week2);
    s.addAll(week3);
    std::cout << "  " << s.count() << " readings, mean " << s.mean() << std::endl;
    return 0;
}
