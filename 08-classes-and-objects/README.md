# Module 8 — Classes and Objects

## From `struct` to `class`

In Module 5, `struct Student` grouped data together. A **class** takes
that idea further: it bundles **data** (called **member variables** or
**attributes**) *and* **behavior** (called **member functions** or
**methods**) into one type. This pairing — data plus the functions that
operate on it, defined together — is the foundation of **object-oriented
programming (OOP)**.

```cpp
class BankAccount {
public:
    std::string ownerName;
    double balance;

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            std::cout << "Insufficient funds!" << std::endl;
        }
    }

    void printStatement() {
        std::cout << ownerName << "'s balance: " << balance << std::endl;
    }
};
```

- **Class** = the blueprint (`BankAccount`).
- **Object** (or **instance**) = an actual variable created from that
  blueprint:

  ```cpp
  int main() {
      BankAccount account;
      account.ownerName = "Ama";
      account.balance = 100.0;

      account.deposit(50.0);
      account.withdraw(30.0);
      account.printStatement();  // Ama's balance: 120

      return 0;
  }
  ```

Notice `deposit` and `withdraw` don't take `balance` as a parameter —
they act *directly* on the calling object's own `balance`. Every method
implicitly has access to the member variables of the specific object it
was called on (`account.deposit(50)` modifies `account`'s balance, not
some other `BankAccount`).

## Access specifiers: `public` and `private`

The example above puts everything under `public:`, meaning any code
outside the class can read or write `ownerName` and `balance` directly —
including setting `balance = -500;`, which makes no real-world sense.
**Encapsulation** is the OOP principle of hiding a class's internal data
and only allowing controlled access through its methods:

```cpp
class BankAccount {
private:
    std::string ownerName;
    double balance;

public:
    void setOwnerName(std::string name) {
        ownerName = name;
    }

    void deposit(double amount) {
        if (amount > 0) {          // now we can enforce a rule
            balance += amount;
        }
    }

    double getBalance() {
        return balance;
    }
};
```

- `private:` members are only accessible from **inside** the class's own
  methods — `account.balance` from `main` would now be a compiler error.
- `public:` methods that read/return a private member are conventionally
  called **getters** (`getBalance`); ones that set a private member,
  usually with validation, are **setters** (`setOwnerName`).
- **Default rule of thumb:** make member variables `private`, and expose
  only what's needed through `public` methods. This is what lets you
  enforce rules like "balance can never go negative" — impossible to
  guarantee if any outside code can just write `balance = -500;` directly.

## Constructors — initializing an object at creation time

Manually setting every field after creating an object (as in the first
example) is error-prone — easy to forget one. A **constructor** is a
special method that runs automatically when an object is created, and
has the exact same name as the class with no return type:

```cpp
class BankAccount {
private:
    std::string ownerName;
    double balance;

public:
    // Constructor
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

int main() {
    BankAccount account("Kofi", 200.0);  // constructor runs immediately
    account.deposit(50.0);
    std::cout << account.getBalance() << std::endl;  // 250
    return 0;
}
```

Once you define *any* constructor, C++ no longer generates the "empty"
default constructor for you — `BankAccount account;` (no arguments)
would now be a compiler error unless you also write a **default
constructor** (one that takes no parameters). This is a real thing you'll
run into — the fix is simply to provide one if you need it:

```cpp
BankAccount() {
    ownerName = "Unknown";
    balance = 0.0;
}
```

Because C++ supports **function overloading** (Module 7), you can define
multiple constructors with different parameter lists, and the compiler
picks the right one based on how you construct the object.

## `this` (a brief, practical look)

Inside a method, `this` is a pointer to "the object the method was
called on." You'll mostly need it only when a parameter name shadows a
member variable name:

```cpp
class Point {
private:
    int x, y;
public:
    Point(int x, int y) {
        this->x = x;   // "this object's x" = the parameter named x
        this->y = y;
    }
};
```

Without `this->`, `x = x;` inside the constructor would just assign the
parameter to itself and never touch the member variable — a subtle,
common bug. You won't need `this` outside of this exact situation for a
while, but recognize it when you see it.

## Classes vs. structs — practical guidance for this course

Technically in C++, `struct` and `class` are almost the same thing (the
only default difference is `struct` members are `public` by default,
`class` members are `private` by default). In practice, the convention
is:
- Use **`struct`** for simple bundles of public data with no behavior
  (like `Student` in Module 5).
- Use **`class`** when you want private data, methods, constructors, and
  enforced rules — i.e., real OOP design.

## Common beginner mistakes

- Trying to access a `private` member from outside the class (compiler
  error — this is the point, not a bug to work around by making
  everything `public`).
- Defining a parameterized constructor and then being surprised
  `MyClass obj;` no longer compiles — add a default constructor if you
  need one.
- Forgetting `this->` when a constructor parameter shares a name with a
  member variable.
- Forgetting the `;` after a class definition's closing `}` (same
  footgun as `struct` in Module 5).

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — a proper
   `BankAccount` simulator with a transaction history.
4. Commit:

   ```bash
   git add 08-classes-and-objects
   git commit -m "Complete Module 8: classes and objects"
   git push
   ```

Next: **[Module 9 — Capstone Project](../09-capstone-project/README.md)**
— where everything from this entire course comes together.
