# Module 11 — Inheritance

Part 1's Module 8 taught you to design a single class. Real programs
usually have several *related* classes that share common data and
behavior but each add something specific — a `SavingsAccount` and a
`CheckingAccount` are both "a kind of" `BankAccount`; a `Resistor` and a
`Capacitor` are both "a kind of" `Component`. **Inheritance** lets you
express that relationship directly in code, instead of copy-pasting the
shared parts into every class.

## The core idea: "is-a"

Inheritance models an **"is-a" relationship**. Ask yourself: "is a
SavingsAccount a kind of BankAccount?" Yes — so `SavingsAccount` can
**inherit from** `BankAccount`, automatically getting everything
`BankAccount` already has, and adding only what's different.

```cpp
class BankAccount {
protected:
    std::string ownerName;
    double balance;

public:
    BankAccount(std::string name, double startingBalance) {
        ownerName = name;
        balance = startingBalance;
    }

    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }

    double getBalance() {
        return balance;
    }
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(std::string name, double startingBalance, double rate)
        : BankAccount(name, startingBalance) {
        interestRate = rate;
    }

    void applyInterest() {
        balance += balance * interestRate; // uses the inherited balance
    }
};
```

- `class SavingsAccount : public BankAccount` — "`SavingsAccount`
  **derives from** `BankAccount`." `BankAccount` is the **base class**
  (or parent/superclass); `SavingsAccount` is the **derived class** (or
  child/subclass).
- `SavingsAccount` automatically has `deposit()` and `getBalance()` —
  you never re-wrote them.
- `: BankAccount(name, startingBalance)` in the constructor's header is
  the **member initializer list** calling the base class's constructor
  first — the base part of the object must be constructed before the
  derived part can add anything to it.

## `protected` — a new access level

Notice `ownerName` and `balance` changed from `private` (Module 8) to
`protected`. Recall the two levels from Module 8:
- `private` — accessible only inside the class itself.
- `public` — accessible from anywhere.

`protected` is a third level, specifically for inheritance:
**accessible inside the class itself, AND inside any class that derives
from it** — but still not from outside code. `SavingsAccount::applyInterest()`
can touch `balance` directly because it inherits from `BankAccount`;
code in `main` still cannot.

## Using the derived class

```cpp
int main() {
    SavingsAccount acc("Ama", 1000.0, 0.05);
    acc.deposit(200.0);        // inherited from BankAccount, unchanged
    acc.applyInterest();       // new, only SavingsAccount has this
    std::cout << acc.getBalance() << std::endl;  // inherited getter works too
    return 0;
}
```

A `SavingsAccount` object contains a complete `BankAccount` "inside" it,
plus its own additions. Every public and protected member of the base
class is available on the derived object as if it had been written
there directly.

## Overriding a method

Sometimes the derived class needs to *change* behavior the base class
already provides, not just add new behavior:

```cpp
class Component {
protected:
    std::string name;
    double value;

public:
    Component(std::string n, double v) : name(n), value(v) {}

    void describe() {
        std::cout << name << ": " << value << std::endl;
    }
};

class Resistor : public Component {
public:
    Resistor(double ohms) : Component("Resistor", ohms) {}

    void describe() {   // this HIDES Component's describe(), for a Resistor object
        std::cout << name << ": " << value << " ohms" << std::endl;
    }
};
```

Calling `describe()` on a `Resistor` object runs `Resistor`'s version.
This works, but it only works reliably when you're calling through a
`Resistor` variable directly. The moment you try to treat a `Resistor`
through a generic `Component` pointer — which is exactly what you'll
want to do to hold a mixed collection of components — this simple
overriding breaks down. That's precisely the gap **Module 12:
Polymorphism** closes, using one new keyword (`virtual`).

## Constructors and inheritance — the order matters

When a derived object is created, construction always happens
**base-first, then derived**:

```cpp
SavingsAccount acc("Ama", 1000.0, 0.05);
// 1. BankAccount(name, startingBalance) runs first
// 2. THEN SavingsAccount's own constructor body runs (setting interestRate)
```

If the base class has no default (no-argument) constructor, the derived
class's constructor **must** explicitly call a base constructor in its
member initializer list, exactly as shown above — there's no way to
skip constructing the base part of the object.

## Common beginner mistakes

- Forgetting to call the base class constructor explicitly when it
  needs arguments — the compiler will refuse to build.
- Using `private` in the base class for members the derived class needs
  to touch directly (use `protected` instead).
- Assuming a derived class automatically gets the base class's
  constructors as its own "for free" — it doesn't; you write the
  derived constructor yourself and call the base one from it.
- Confusing "hiding" a method (this module) with true polymorphic
  overriding (`virtual`, next module) — they look similar but behave
  very differently through base-class pointers, as you'll see next.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — pick the Generic,
   EE, or Biomedical track.
4. Commit:

   ```bash
   git add 11-inheritance
   git commit -m "Complete Module 11: inheritance"
   git push
   ```

Next: **[Module 12 — Polymorphism & Virtual Functions](../12-polymorphism/README.md)**.
