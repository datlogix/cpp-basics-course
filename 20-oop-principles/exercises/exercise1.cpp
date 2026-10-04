// Exercise 1: OOP Principles & Object Modelling
//
// PROBLEM STATEMENT
//   "An intercity bus company runs buses between Accra and Kumasi. Each
//    bus has a registration number and a fixed number of seats. A
//    passenger buys a ticket for a seat on a bus. A ticket shows the
//    passenger's name, the seat number, and the fare. A bus must never
//    sell the same seat twice, and must never sell more tickets than it
//    has seats. The station manager can print a passenger list for a bus."
//
// TODO 1: In the comment block below, list the NOUNS and VERBS from the
//         problem statement, and decide for each noun whether it is a
//         class, an attribute, or neither (with a one-line reason).
// TODO 2: Write a class Ticket with private passengerName, seatNumber,
//         and fare, a constructor, and const getters.
// TODO 3: Write a class Bus with a private registration number, a seat
//         capacity, and a std::vector<Ticket>. Give it:
//           - bool sellTicket(std::string passenger, int seat, double fare)
//             returning false (and selling nothing) if the seat number is
//             outside 1..capacity, OR the seat is already taken.
//           - void printPassengerList() const
// TODO 4: In main, create a bus with 4 seats, sell some tickets, and
//         prove that a duplicate seat and an out-of-range seat are both
//         refused.
//
// Compile and run:
//   g++ -std=c++17 -Wall -Wextra exercise1.cpp -o exercise1
//   ./exercise1
#include <iostream>
#include <string>
#include <vector>

/*
  TODO 1 - Noun/verb analysis

  Nouns:
    -

  Verbs:
    -
*/

class Ticket {
    // TODO 2
};

class Bus {
    // TODO 3
};

int main() {
    // TODO 4

    return 0;
}
