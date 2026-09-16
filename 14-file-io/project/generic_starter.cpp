// Module 14 Project - Track A: Expense Log
// See project/README.md for requirements.
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string category;
    double amount;
    std::cout << "Category: ";
    std::cin >> category;
    std::cout << "Amount: ";
    std::cin >> amount;

    // TODO: append "<category>,<amount>" to expenses.csv using std::ios::app.

    // TODO: read the whole file back, printing every entry.

    // TODO: compute and print the total spent across all entries.

    return 0;
}
