#include <iostream>
#include <string>
#include <vector>

/*
  Noun/verb analysis

  Nouns:
    - bus company    -> neither: it's the context, not something we model here
    - bus            -> CLASS: has data (seats, tickets) and rules
    - registration   -> attribute of Bus
    - seats          -> attribute of Bus (a capacity number)
    - passenger      -> attribute of Ticket (just a name, no behaviour yet)
    - ticket         -> CLASS: groups name + seat + fare together
    - seat number    -> attribute of Ticket
    - fare           -> attribute of Ticket
    - station manager-> neither: the USER of the program
    - passenger list -> neither: the OUTPUT of a method

  Verbs:
    - buys a ticket            -> Bus::sellTicket(...)
    - never sell the same seat -> a RULE enforced inside sellTicket
    - print a passenger list   -> Bus::printPassengerList()
*/

class Ticket {
private:
    std::string passengerName;
    int seatNumber;
    double fare;

public:
    Ticket(std::string name, int seat, double f)
        : passengerName(name), seatNumber(seat), fare(f) {}

    std::string getPassengerName() const { return passengerName; }
    int getSeatNumber() const { return seatNumber; }
    double getFare() const { return fare; }
};

class Bus {
private:
    std::string registration;
    int capacity;
    std::vector<Ticket> tickets;

    bool isSeatTaken(int seat) const {
        for (const Ticket& t : tickets) {
            if (t.getSeatNumber() == seat) {
                return true;
            }
        }
        return false;
    }

public:
    Bus(std::string reg, int seats) : registration(reg), capacity(seats) {}

    bool sellTicket(std::string passenger, int seat, double fare) {
        if (seat < 1 || seat > capacity) {
            return false;
        }
        if (isSeatTaken(seat)) {
            return false;
        }
        tickets.push_back(Ticket(passenger, seat, fare));
        return true;
    }

    void printPassengerList() const {
        std::cout << "Passenger list for bus " << registration << ":" << std::endl;
        for (const Ticket& t : tickets) {
            std::cout << "  Seat " << t.getSeatNumber() << ": " << t.getPassengerName()
                      << " (GHS " << t.getFare() << ")" << std::endl;
        }
        std::cout << "  " << tickets.size() << " of " << capacity << " seats sold" << std::endl;
    }
};

int main() {
    Bus bus("GR-2468-26", 4);

    bus.sellTicket("Ama Serwaa", 1, 180.0);
    bus.sellTicket("Yaw Boateng", 2, 180.0);

    if (!bus.sellTicket("Esi Quaye", 2, 180.0)) {
        std::cout << "Refused: seat 2 is already taken." << std::endl;
    }
    if (!bus.sellTicket("Kojo Asante", 9, 180.0)) {
        std::cout << "Refused: seat 9 does not exist on this bus." << std::endl;
    }

    bus.printPassengerList();
    return 0;
}
