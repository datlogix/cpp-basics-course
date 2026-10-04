#pragma once

#include <iostream>

namespace makersplace::school {

// Ghana cedis, stored as whole pesewas (Stage 1 and Stage 3).
class Money {
private:
    long pesewas = 0;

public:
    Money() = default;
    explicit Money(long p) : pesewas(p) {}
    static Money fromCedis(double cedis);
    long inPesewas() const { return pesewas; }

    Money& operator+=(const Money& other);
    // TODO (Stage 3): -=, *, /, unary -, <=>, ==, >> ...

    friend std::ostream& operator<<(std::ostream& os, const Money& m);
};

Money operator+(Money a, const Money& b);

} // namespace makersplace::school
