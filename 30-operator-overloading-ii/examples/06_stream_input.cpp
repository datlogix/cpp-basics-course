// operator>> mirrors operator<<: a non-member friend that takes the stream
// and a NON-const reference, and returns the stream. It works with ANY
// input stream - cin, files, or (as here) string streams.
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

class Money {
private:
    long pesewas = 0;

public:
    Money() {}
    explicit Money(long p) : pesewas(p) {}

    Money& operator+=(const Money& other) {
        pesewas += other.pesewas;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Money& m) {
        os << "GHS " << m.pesewas / 100 << "." << std::setw(2) << std::setfill('0') << m.pesewas % 100
           << std::setfill(' ');
        return os;
    }

    friend std::istream& operator>>(std::istream& in, Money& m) {
        double cedis;
        if (in >> cedis) {                      // only change m if the read worked
            m.pesewas = std::lround(cedis * 100);
        }
        return in;
    }
};

int main() {
    // A string stream stands in for the keyboard or a file.
    std::istringstream receipts("12.50 7.25 100 abc 3.00");

    Money total;
    Money item;
    while (receipts >> item) { // stops at "abc" - the stream fails, exactly like reading an int
        std::cout << "  read " << item << std::endl;
        total += item;
    }
    std::cout << "Total of valid receipts: " << total << std::endl;

    // The same operator works with the keyboard:
    //   Money m;
    //   std::cout << "Amount: ";
    //   if (std::cin >> m) { std::cout << "You entered " << m << std::endl; }
    return 0;
}
