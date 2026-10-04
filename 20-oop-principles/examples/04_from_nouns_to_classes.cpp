// The school fees problem statement from the README, turned into code
// using noun/verb analysis:
//
//   "A school enrols students. Each student has a name, a student ID,
//    and a fee account. The fee account records payments and knows the
//    balance still owed. A bursar records a payment of an amount on a
//    date, and can print a statement for any student."
//
// Nouns that became classes: School, Student, FeeAccount, Payment.
// Nouns that became attributes: name, studentId, amount, date.
// "balance" is CALCULATED, not stored - it can never disagree with
// the list of payments.
//
// Compile and run:
//   g++ -std=c++17 -Wall -Wextra 04_from_nouns_to_classes.cpp -o 04_from_nouns_to_classes
//   ./04_from_nouns_to_classes
#include <iostream>
#include <string>
#include <vector>

class Payment {
private:
    double amount;
    std::string date;

public:
    Payment(double a, std::string d) : amount(a), date(d) {}
    double getAmount() const { return amount; }
    std::string getDate() const { return date; }
};

class FeeAccount {
private:
    double totalFees;
    std::vector<Payment> payments;

public:
    FeeAccount(double fees) : totalFees(fees) {}

    // verb: "records a payment"
    bool recordPayment(Payment p) {
        if (p.getAmount() <= 0) {
            return false; // the account protects its own rule
        }
        payments.push_back(p);
        return true;
    }

    // verb: "knows the balance" - calculated, never stored
    double balance() const {
        double paid = 0;
        for (const Payment& p : payments) {
            paid += p.getAmount();
        }
        return totalFees - paid;
    }

    void printPayments() const {
        for (const Payment& p : payments) {
            std::cout << "  " << p.getDate() << "  GHS " << p.getAmount() << std::endl;
        }
    }
};

class Student {
private:
    std::string name;
    std::string studentId;
    FeeAccount account;

public:
    Student(std::string n, std::string id, double fees)
        : name(n), studentId(id), account(fees) {}

    std::string getId() const { return studentId; }
    FeeAccount& getAccount() { return account; }

    // verb: "print a statement"
    void printStatement() const {
        std::cout << "Statement for " << name << " (" << studentId << ")" << std::endl;
        account.printPayments();
        std::cout << "  Balance owed: GHS " << account.balance() << std::endl;
    }
};

class School {
private:
    std::vector<Student> students;

public:
    // verb: "enrols"
    void enrol(Student s) { students.push_back(s); }

    Student* find(std::string id) {
        for (Student& s : students) {
            if (s.getId() == id) {
                return &s;
            }
        }
        return nullptr;
    }
};

int main() {
    School school;
    school.enrol(Student("Akosua Mensah", "MP-001", 1500.0));
    school.enrol(Student("Kwame Owusu", "MP-002", 1500.0));

    Student* akosua = school.find("MP-001");
    if (akosua != nullptr) {
        akosua->getAccount().recordPayment(Payment(500.0, "2026-09-01"));
        akosua->getAccount().recordPayment(Payment(250.0, "2026-10-01"));
        akosua->getAccount().recordPayment(Payment(-90.0, "2026-10-02")); // rejected
        akosua->printStatement();
    }

    return 0;
}
