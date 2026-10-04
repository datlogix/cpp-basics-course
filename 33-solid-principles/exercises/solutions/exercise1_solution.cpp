#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

/*
  SMELLS found in the original CanteenManager:
  - God class: CanteenManager owns the menu, prices orders, applies payment
    fees, prints receipts AND notifies - five reasons to change (breaks SRP).
  - Long method: placeOrder() does everything in one 30-line function.
  - Switch on type: the if/else chain on paymentType must be edited for
    every new payment method (breaks OCP).
  - Primitive obsession: payment types are bare strings - a typo ("Momo")
    silently becomes "unknown".
  - Hard-wired dependency: ConsoleNotifier is created inside the class, so
    it can't be replaced by SMS or a fake for testing (breaks DIP).
  - Long parameter passing by value of vectors/strings (minor).
*/

// ---------- The menu (SRP) ----------
class Menu {
private:
    std::map<std::string, double> prices;

public:
    void add(const std::string& item, double price) { prices[item] = price; }
    bool has(const std::string& item) const { return prices.count(item) > 0; }
    double priceOf(const std::string& item) const { return prices.at(item); }
};

// ---------- Payment methods (OCP) ----------
class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;
    virtual std::string name() const = 0;
    virtual double fee(double subtotal) const = 0;
};

class Cash : public PaymentMethod {
public:
    std::string name() const override { return "cash"; }
    double fee(double) const override { return 0; }
};

class MobileMoney : public PaymentMethod {
public:
    std::string name() const override { return "momo"; }
    double fee(double subtotal) const override { return subtotal * 0.01; }
};

class Card : public PaymentMethod {
public:
    std::string name() const override { return "card"; }
    double fee(double subtotal) const override { return 0.50 + subtotal * 0.02; }
};

// Payment methods are looked up by name. A new method is ADDED by
// registering it - nothing here needs editing.
class PaymentRegistry {
private:
    std::map<std::string, std::unique_ptr<PaymentMethod>> methods;

public:
    void add(std::unique_ptr<PaymentMethod> m) {
        std::string key = m->name();
        methods[key] = std::move(m);
    }
    const PaymentMethod* find(const std::string& name) const {
        auto it = methods.find(name);
        return it == methods.end() ? nullptr : it->second.get();
    }
};

// ---------- Notification (DIP) ----------
class Notifier {
public:
    virtual ~Notifier() = default;
    virtual void notify(const std::string& message) = 0;
};

class ConsoleNotifier : public Notifier {
public:
    void notify(const std::string& message) override { std::cout << "  >> " << message << std::endl; }
};

// ---------- The order desk: only coordinates ----------
class OrderDesk {
private:
    const Menu& menu;
    const PaymentRegistry& payments;
    Notifier& notifier; // injected

    double printItemsAndSubtotal(const std::vector<std::string>& items) const {
        double subtotal = 0;
        for (const std::string& item : items) {
            if (!menu.has(item)) {
                std::cout << "  (no " << item << " today)" << std::endl;
                continue;
            }
            std::cout << "  " << std::left << std::setw(14) << item << std::right << std::fixed
                      << std::setprecision(2) << menu.priceOf(item) << std::endl;
            subtotal += menu.priceOf(item);
        }
        return subtotal;
    }

public:
    OrderDesk(const Menu& m, const PaymentRegistry& p, Notifier& n) : menu(m), payments(p), notifier(n) {}

    void placeOrder(const std::string& student, const std::vector<std::string>& items,
                    const std::string& paymentName) {
        std::cout << "Order for " << student << ":" << std::endl;
        double subtotal = printItemsAndSubtotal(items);
        const PaymentMethod* payment = payments.find(paymentName);
        if (payment == nullptr) {
            std::cout << "  unknown payment type " << paymentName << std::endl;
            return;
        }
        double fee = payment->fee(subtotal);
        std::cout << "  subtotal " << subtotal << ", fee " << fee << ", total " << subtotal + fee << " ("
                  << payment->name() << ")" << std::endl;
        notifier.notify(student + "'s order is being prepared");
    }
};

int main() {
    Menu menu;
    menu.add("jollof rice", 15.0);
    menu.add("waakye", 12.0);
    menu.add("kelewele", 6.0);
    menu.add("sobolo", 4.0);

    PaymentRegistry payments;
    payments.add(std::make_unique<Cash>());
    payments.add(std::make_unique<MobileMoney>());
    payments.add(std::make_unique<Card>());

    ConsoleNotifier console;
    OrderDesk desk(menu, payments, console);

    desk.placeOrder("Ama", {"jollof rice", "sobolo"}, "cash");
    desk.placeOrder("Kojo", {"waakye", "kelewele", "pizza"}, "momo");
    desk.placeOrder("Esi", {"jollof rice", "kelewele", "sobolo"}, "card");
    desk.placeOrder("Yaw", {"waakye"}, "cheque");

    // TODO 5 would add a new class
    //   class Voucher : public PaymentMethod { ... };
    // plus one line here:  payments.add(std::make_unique<Voucher>());
    // with NO edits to Menu, PaymentMethod, Cash, MobileMoney, Card,
    // PaymentRegistry or OrderDesk. (The GHS 20 limit suggests PaymentMethod
    // might grow a virtual "maximum amount" - a good discussion point: is
    // that an edit to existing code, and is it justified?)
    return 0;
}
