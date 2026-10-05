// C++ Foundations Project Book - Chapter 5, Activity 3: Canteen Orders
// Difficulty: CHALLENGE
//
// Use only: everything from Modules 1-4, plus arrays, std::vector
// (push_back, pop_back, size), range-based for loops, std::string as a
// sequence (length() and [ ]), and struct.
// Not yet: your own functions (Module 6) - all code lives inside main.
//
// Compile and run (from this folder):
//     g++ canteen_orders.cpp -o canteen_orders
//     ./canteen_orders
#include <iostream>
#include <string>
#include <vector>

struct MenuItem {
    std::string name;
    double price;
};

int main() {
    // TODO 1: Fill the menu with at least five items. One is done for you.
    std::vector<MenuItem> menu;
    MenuItem jollof;
    jollof.name = "Jollof rice";
    jollof.price = 25.00;
    menu.push_back(jollof);

    std::vector<MenuItem> order;

    // TODO 2: Print the menu, numbered from 1.

    // TODO 3: Let the customer type item numbers, one at a time, until they
    //         type 0. Reject any number that doesn't match an item.
    //         Add each chosen item to order with push_back.

    // TODO 4: If the customer types -1, remove the LAST item they ordered
    //         with pop_back - but only if order isn't empty.

    // TODO 5: When they finish, print the order, its total, and the most
    //         expensive item in it.

    return 0;
}
