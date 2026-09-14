# Module 8 Project — Bank Account Simulator

Build a proper `BankAccount` class and drive it from a simple text menu.
This combines nearly everything from the whole course: classes, vectors,
loops, `if`, functions.

## `BankAccount` class requirements

Private members:
- `std::string ownerName`
- `double balance`
- `std::vector<std::string> transactionHistory`

Public methods:
1. `BankAccount(std::string name, double startingBalance)` — constructor.
   Record `"Account opened with balance <startingBalance>"` as the first
   transaction.
2. `void deposit(double amount)` — rejects (prints an error, does
   nothing) if `amount <= 0`. Otherwise increases balance and appends a
   record like `"Deposited 50"` to `transactionHistory`.
3. `void withdraw(double amount)` — rejects if `amount <= 0` or
   `amount > balance` (print a clear reason why). Otherwise decreases
   balance and records `"Withdrew 30"`.
4. `double getBalance()` — returns the current balance.
5. `void printHistory()` — prints every entry in `transactionHistory`,
   numbered.

## `main` — a menu-driven program

Using a `do-while` loop (Module 4), show a menu like:

```
1. Deposit
2. Withdraw
3. Check balance
4. Print history
5. Exit
```

Read the user's choice, `switch` on it (Module 4) to call the right
method, and loop until they choose Exit.

## Starter file

Open [`starter.cpp`](starter.cpp) — the class skeleton and menu loop
structure are stubbed for you.

## When you're done

```bash
g++ starter.cpp -o bank_simulator
./bank_simulator
```

```bash
git add 08-classes-and-objects
git commit -m "Complete Module 8 project: bank account simulator"
git push
```

This is your last stop before the **[Capstone Project](../09-capstone-project/README.md)** — where you'll build one larger program from scratch using everything from Modules 1–8.
