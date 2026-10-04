// Prefix ++/-- return *this by reference (the NEW value).
// Postfix ++/-- take a dummy int and return the OLD value by value.
#include <iostream>
#include <string>

class ClassPeriod {
private:
    int period; // 1..8 in a school day
    static const int FIRST = 1;
    static const int LAST = 8;

public:
    explicit ClassPeriod(int p) : period(p < FIRST ? FIRST : (p > LAST ? LAST : p)) {}

    ClassPeriod& operator++() { // prefix: ++p
        if (period < LAST) {
            ++period;
        }
        return *this;
    }

    ClassPeriod operator++(int) { // postfix: p++
        ClassPeriod old = *this;
        ++(*this); // reuse the prefix version
        return old;
    }

    ClassPeriod& operator--() { // prefix: --p
        if (period > FIRST) {
            --period;
        }
        return *this;
    }

    ClassPeriod operator--(int) { // postfix: p--
        ClassPeriod old = *this;
        --(*this);
        return old;
    }

    friend std::ostream& operator<<(std::ostream& os, const ClassPeriod& p) {
        os << "period " << p.period;
        return os;
    }
};

int main() {
    ClassPeriod now(3);

    std::cout << "now:          " << now << std::endl;
    std::cout << "++now gives:  " << ++now << "  (new value)" << std::endl;
    std::cout << "now++ gives:  " << now++ << "  (OLD value)" << std::endl;
    std::cout << "now is:       " << now << std::endl;
    std::cout << "--now gives:  " << --now << std::endl;

    ClassPeriod last(8);
    ++last; // stays within the school day
    std::cout << "after the last period: " << last << std::endl;
    return 0;
}
