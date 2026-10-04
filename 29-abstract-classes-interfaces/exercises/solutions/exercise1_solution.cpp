#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Payable {
public:
    virtual ~Payable() = default;
    virtual std::string payee() const = 0;
    virtual double amountDueGhs() const = 0;
};

class Employee : public Payable {
protected:
    std::string name;

    virtual double grossPay() const = 0;
    virtual double taxRate() const = 0;

public:
    explicit Employee(std::string n) : name(n) {}

    std::string payee() const override { return name; }

    double amountDueGhs() const override {
        return grossPay() * (1 - taxRate());
    }

    void printPayslip() const { // Template Method: same steps for every employee
        double gross = grossPay();
        double tax = gross * taxRate();
        std::cout << "  Payslip: " << name << "  gross " << gross << "  tax " << tax
                  << "  net " << gross - tax << std::endl;
    }

    virtual std::unique_ptr<Employee> clone() const = 0;
};

class SalariedEmployee : public Employee {
private:
    double monthlySalary;

protected:
    double grossPay() const override { return monthlySalary; }
    double taxRate() const override { return 0.15; }

public:
    SalariedEmployee(std::string n, double salary) : Employee(n), monthlySalary(salary) {}
    void giveRaise(double amount) { monthlySalary += amount; }
    std::unique_ptr<Employee> clone() const override { return std::make_unique<SalariedEmployee>(*this); }
};

class HourlyEmployee : public Employee {
private:
    double hours;
    double ratePerHour;

protected:
    double grossPay() const override { return hours * ratePerHour; }
    double taxRate() const override { return 0.10; }

public:
    HourlyEmployee(std::string n, double h, double rate) : Employee(n), hours(h), ratePerHour(rate) {}
    std::unique_ptr<Employee> clone() const override { return std::make_unique<HourlyEmployee>(*this); }
};

class Supplier : public Payable {
private:
    std::string company;
    double invoiceGhs;

public:
    Supplier(std::string c, double invoice) : company(c), invoiceGhs(invoice) {}
    std::string payee() const override { return company; }
    double amountDueGhs() const override { return invoiceGhs; }
};

double payAll(const std::vector<const Payable*>& items) {
    double total = 0;
    for (const Payable* p : items) {
        std::cout << "  pay " << p->payee() << ": GHS " << p->amountDueGhs() << std::endl;
        total += p->amountDueGhs();
    }
    return total;
}

int main() {
    std::vector<std::unique_ptr<Employee>> staff;
    staff.push_back(std::make_unique<SalariedEmployee>("Mrs Addo", 4500));
    staff.push_back(std::make_unique<HourlyEmployee>("Mr Tetteh (part-time coach)", 40, 55));
    Supplier labService("Accra Computer Services Ltd", 2800);

    std::cout << "Payslips:" << std::endl;
    for (const auto& e : staff) {
        e->printPayslip();
    }

    std::vector<const Payable*> payables;
    for (const auto& e : staff) {
        payables.push_back(e.get());
    }
    payables.push_back(&labService);

    std::cout << "Payment run:" << std::endl;
    double total = payAll(payables);
    std::cout << "  TOTAL: GHS " << total << std::endl;

    std::cout << "Cloning:" << std::endl;
    std::unique_ptr<Employee> copy = staff[0]->clone();
    if (SalariedEmployee* s = dynamic_cast<SalariedEmployee*>(copy.get())) {
        s->giveRaise(500); // only the copy changes
    }
    staff[0]->printPayslip();
    copy->printPayslip();

    int employees = 0;
    for (const Payable* p : payables) {
        if (dynamic_cast<const Employee*>(p) != nullptr) {
            employees++;
        }
    }
    std::cout << employees << " of " << payables.size() << " payees are employees" << std::endl;

    // dynamic_cast is acceptable for this one-off REPORTING question ("how
    // many of these are employees?"). Using it to CALCULATE pay - "if it's a
    // SalariedEmployee do this, else if Hourly do that" - would be a smell:
    // every new kind of payee would need another branch, whereas the virtual
    // amountDueGhs() already handles every current and future type.
    return 0;
}
