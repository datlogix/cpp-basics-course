// friend functions and friend classes: access granted BY the class,
// declared INSIDE the class, next to the members they use.
#include <iomanip>
#include <iostream>

class Money {
private:
    long pesewas; // 1 cedi = 100 pesewas; whole numbers avoid rounding errors

public:
    explicit Money(long p) : pesewas(p) {}

    // A friend FUNCTION: not a member, but may read pesewas.
    friend std::ostream& operator<<(std::ostream& os, const Money& m);

    // A friend CLASS: every Auditor method may read Money's private members.
    friend class Auditor;
};

std::ostream& operator<<(std::ostream& os, const Money& m) {
    os << "GHS " << m.pesewas / 100 << "." << std::setw(2) << std::setfill('0') << m.pesewas % 100
       << std::setfill(' ');
    return os;
}

class Auditor {
public:
    bool looksSuspicious(const Money& m) const {
        return m.pesewas % 100000 == 0; // suspiciously round amounts (multiples of GHS 1000)
    }
};

int main() {
    Money fees(150050);   // GHS 1500.50
    Money transfer(500000); // GHS 5000.00

    std::cout << fees << std::endl;
    std::cout << transfer << std::endl;

    Auditor auditor;
    std::cout << "fees suspicious? " << (auditor.looksSuspicious(fees) ? "yes" : "no") << std::endl;
    std::cout << "transfer suspicious? " << (auditor.looksSuspicious(transfer) ? "yes" : "no") << std::endl;
    // std::cout << fees.pesewas;  // ERROR: main is not a friend
    return 0;
}
