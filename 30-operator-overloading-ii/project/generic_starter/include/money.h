// JUDGEMENT TABLE (requirement 7): every operator considered, provided or
// rejected, and why.
//
//   operator      provided?   reason
//   --------      ---------   ------
//
#pragma once

#include <compare>
#include <iostream>
#include <map>
#include <string>

namespace makersplace::school {

class Money {
private:
    long pesewas = 0;

public:
    Money() {}
    explicit Money(long p) : pesewas(p) {}
    static Money fromCedis(double cedis);

    long inPesewas() const { return pesewas; }

    Money& operator+=(const Money& other);
    // TODO: -=, *= (by int), /= (by int - document the leftover pesewas rule)
    // TODO: unary minus

    // TODO: <=> and ==

    friend std::ostream& operator<<(std::ostream& os, const Money& m); // TODO: "GHS 1,250.50"
    friend std::istream& operator>>(std::istream& in, Money& m);       // TODO
};

Money operator+(Money a, const Money& b);
// TODO: -, Money * int, int * Money, Money / int

class FeeLedger {
private:
    std::map<std::string, Money> balances;

public:
    Money& operator[](const std::string& studentId);             // creates a zero balance if new
    const Money& operator[](const std::string& studentId) const; // TODO: throw std::out_of_range if unknown
    // TODO: a way for algorithms to look at every balance (e.g. return a std::vector<Money>)
};

// TODO: functor OwesMoreThan

} // namespace makersplace::school
