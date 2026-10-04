// Exercise 1: SOLID Principles & Clean Design - a refactoring exercise
//
// CanteenManager below WORKS, but it is a "god class". Your job is to
// refactor it WITHOUT changing what the program prints.
//
// TODO 1: Before changing anything, run the program and save its output:
//           ./exercise1 > before.txt
// TODO 2: In the SMELLS comment block, list every code smell you can find
//         (use the table in the README), with the line or method where it
//         appears, and which SOLID principle it breaks.
// TODO 3: Refactor, in small steps, compiling and re-running after each:
//           - SRP: separate the menu, the order/receipt calculation, and
//             the notification into their own classes.
//           - OCP: replace the switch on payment type with a PaymentMethod
//             abstract class (Cash, MobileMoney, Card), so a new payment
//             method can be ADDED without editing existing code.
//           - DIP: the class that confirms an order must receive a
//             Notifier& (an interface) through its constructor instead of
//             creating a ConsoleNotifier itself.
// TODO 4: When you're done, check the behaviour is unchanged:
//           ./exercise1 > after.txt
//           diff before.txt after.txt      (no output means identical)
// TODO 5: Prove OCP: add a new "Voucher" payment method (no fee, but at most
//         GHS 20 can be paid by voucher) WITHOUT editing any existing class.
//         (This changes the output, so do it after TODO 4.)
//
// Compile and run:
//   g++ -std=c++17 -Wall -Wextra exercise1.cpp -o exercise1
//   ./exercise1
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

/*
  SMELLS (TODO 2):

*/

class ConsoleNotifier {
public:
    void notify(const std::string& message) { std::cout << "  >> " << message << std::endl; }
};

class CanteenManager {
private:
    std::map<std::string, double> menu;
    ConsoleNotifier notifier;

public:
    CanteenManager() {
        menu["jollof rice"] = 15.0;
        menu["waakye"] = 12.0;
        menu["kelewele"] = 6.0;
        menu["sobolo"] = 4.0;
    }

    void placeOrder(std::string student, std::vector<std::string> items, std::string paymentType) {
        double subtotal = 0;
        std::cout << "Order for " << student << ":" << std::endl;
        for (size_t i = 0; i < items.size(); i++) {
            if (menu.count(items[i]) == 0) {
                std::cout << "  (no " << items[i] << " today)" << std::endl;
                continue;
            }
            std::cout << "  " << std::left << std::setw(14) << items[i] << std::right << std::fixed
                      << std::setprecision(2) << menu[items[i]] << std::endl;
            subtotal += menu[items[i]];
        }
        double fee = 0;
        if (paymentType == "cash") {
            fee = 0;
        } else if (paymentType == "momo") {
            fee = subtotal * 0.01; // 1% mobile money charge
        } else if (paymentType == "card") {
            fee = 0.50 + subtotal * 0.02;
        } else {
            std::cout << "  unknown payment type " << paymentType << std::endl;
            return;
        }
        double total = subtotal + fee;
        std::cout << "  subtotal " << subtotal << ", fee " << fee << ", total " << total << " (" << paymentType
                  << ")" << std::endl;
        notifier.notify(student + "'s order is being prepared");
    }
};

int main() {
    CanteenManager canteen;
    canteen.placeOrder("Ama", {"jollof rice", "sobolo"}, "cash");
    canteen.placeOrder("Kojo", {"waakye", "kelewele", "pizza"}, "momo");
    canteen.placeOrder("Esi", {"jollof rice", "kelewele", "sobolo"}, "card");
    canteen.placeOrder("Yaw", {"waakye"}, "cheque");
    return 0;
}
