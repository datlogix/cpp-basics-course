#include "money.h"

#include <iostream>
#include <sstream>

using namespace makersplace::school;

int main() {
    Money termFees = Money::fromCedis(1250.50);
    Money pta = Money::fromCedis(80);
    std::cout << "Term fees + PTA dues: " << termFees + pta << std::endl;

    FeeLedger ledger;
    ledger["MP-001"] += termFees;
    ledger["MP-002"] += termFees + pta;
    std::cout << "MP-002 owes " << ledger["MP-002"] << std::endl;

    // TODO: three terms of fees with  3 * termFees  and  termFees * 3
    // TODO: split a GHS 1000.00 bus hire between 3 clubs with  /  - and handle the leftover
    // TODO: read payments from  std::istringstream("500 250.75 abc")  with  >>
    // TODO: compare balances with <, ==, <=>
    // TODO: count students owing more than GHS 500 with std::count_if and OwesMoreThan
    return 0;
}
