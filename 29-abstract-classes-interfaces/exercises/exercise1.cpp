// Exercise 1: Abstract Classes, Interfaces & Advanced Polymorphism
//
// A school pays two kinds of people: its EMPLOYEES and its SUPPLIERS
// (e.g. the company that services the computer lab). Both must be paid,
// but a supplier is not an employee.
//
// TODO 1: Write an INTERFACE Payable with:
//           virtual std::string payee() const = 0;
//           virtual double amountDueGhs() const = 0;
//         and a virtual destructor (= default).
// TODO 2: Write an ABSTRACT class Employee : public Payable with a
//         protected name, and:
//           - protected pure virtual double grossPay() const and
//             double taxRate() const
//           - double amountDueGhs() const override, implemented ONCE in
//             Employee as grossPay() * (1 - taxRate())
//           - a NON-virtual void printPayslip() const that prints the
//             name, gross pay, tax, and net pay using those functions
//             (the Template Method idea)
//           - virtual std::unique_ptr<Employee> clone() const = 0;
// TODO 3: Write two concrete employees:
//           SalariedEmployee - a fixed monthly salary, 15% tax
//           HourlyEmployee   - hours x rate, 10% tax
// TODO 4: Write Supplier : public Payable (NOT an Employee) with a
//         company name and an invoice amount (no tax deducted).
// TODO 5: Write double payAll(const std::vector<const Payable*>& items)
//         that prints each payee and amount and returns the total. It
//         must not mention Employee or Supplier anywhere.
// TODO 6: In main, clone() one employee from a
//         std::vector<std::unique_ptr<Employee>>, and show the clone is a
//         separate object of the right type (change it, print both).
// TODO 7: Use dynamic_cast to count how many of the Payables are
//         Employees. Then, in a comment, explain why this use is
//         acceptable here, but why using dynamic_cast to CALCULATE pay
//         would be a design smell.
//
// Compile and run:
//   g++ -std=c++17 -Wall -Wextra exercise1.cpp -o exercise1
//   ./exercise1
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// TODO 1-4

int main() {
    // TODO 5-7

    return 0;
}
