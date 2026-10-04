# Module 21 — Class Design in Depth

Module 8 taught you enough about classes to get started: `private`
data, `public` methods, constructors, and `this`. Module 20 showed you
how to decide *which* classes a program needs. This module goes back
inside a single class and teaches you the tools professionals use to
make a class **correct, safe, and pleasant to use**:

- member initializer lists and default member values
- constructor overloading and delegating constructors
- `explicit` constructors
- `const` member functions and `const` objects
- class invariants — and why "a getter and setter for everything" is
  usually *not* good design
- `static` members that belong to the class, not to any one object
- `mutable` (briefly)
- defining member functions *outside* the class body

None of these is complicated on its own. Together, they are the
difference between a class that merely compiles and a class that's
hard to misuse.

## Member initializer lists — initialise, don't assign

You've seen two ways to set member variables in a constructor. Module 8
used **assignment inside the body**:

```cpp
class Student {
private:
    std::string name;
    int age;
public:
    Student(std::string n, int a) {
        name = n;   // assignment
        age = a;    // assignment
    }
};
```

Part 2 code often used a **member initializer list** — the part after
the colon:

```cpp
Student(std::string n, int a) : name(n), age(a) {}
```

They look like two spellings of the same thing, but they are not.
Every member is **constructed before the constructor body starts
running**. With the first version, `name` is first constructed as an
empty string, *then* the body overwrites it. With the initializer list,
`name` is constructed with the right value straight away — once.

For an `int` the difference is invisible. But some members **cannot be
assigned at all**, only initialised, and for those the initializer
list is the *only* option:

```cpp
class Patient {
private:
    const std::string folderNumber;   // const: can never change after creation
    Ward& ward;                       // reference: must refer to something from birth
public:
    Patient(std::string folder, Ward& w)
        : folderNumber(folder), ward(w) {}   // OK

    // Patient(std::string folder, Ward& w) {
    //     folderNumber = folder;   // ERROR: can't assign to a const
    //     ward = w;                // wrong: would copy INTO whatever ward refers to
    // }
};
```

Base classes are the same: Module 11 showed that a derived constructor
must construct its base part in the initializer list
(`: Component("Resistor", ohms)`).

**Rule of thumb from now on: initialise every member in the initializer
list.** Use the constructor body only for work that can't be expressed
as initialisation, such as validation.

### Initialisation order

Members are initialised in the order they are **declared in the
class**, not the order you write them in the initializer list:

```cpp
class Range {
private:
    int low;
    int high;
public:
    Range(int width) : high(width), low(high - width) {}  // BUG!
};
```

`low` is declared first, so it is initialised first — using `high`,
which hasn't been initialised yet. `-Wall` warns about this
(`-Wreorder`). Write the initializer list in the same order as the
declarations, and don't make one member's initial value depend on a
member declared after it.

## Default member initializers

You can give a member a default value right where it's declared:

```cpp
class Thermostat {
private:
    double targetCelsius = 24.0;
    bool heatingOn = false;
    std::string location = "Unnamed room";
public:
    Thermostat() {}                                   // uses all the defaults
    Thermostat(std::string loc) : location(loc) {}    // overrides just one
};
```

A value in the initializer list wins over the default. The defaults
mean you can't *forget* to initialise something, no matter how many
constructors you add later — an uninitialised `int` or `bool` member
holds garbage, and reading garbage is one of the most common hidden
bugs in C++.

## Constructor overloading and delegating constructors

A class can have several constructors with different parameter lists
(you saw this in Module 8). The problem is repetition: if every
constructor has to validate the same data, you end up writing the same
checks several times.

A **delegating constructor** hands the work to another constructor of
the same class:

```cpp
class Resistor {
private:
    double ohms;
    double tolerancePercent;
public:
    // The "main" constructor - all validation lives here, once.
    Resistor(double r, double tol) : ohms(r), tolerancePercent(tol) {
        if (ohms <= 0) ohms = 1.0;
        if (tolerancePercent <= 0) tolerancePercent = 5.0;
    }

    // Delegates: "a resistor with no tolerance given is a 5% resistor".
    Resistor(double r) : Resistor(r, 5.0) {}
};
```

The delegating constructor's initializer list contains *only* the call
to the other constructor. Its body (if any) runs after the target
constructor has completely finished.

## `explicit` — stop surprise conversions

A constructor that can be called with **one argument** is also, quietly,
a **conversion** from that argument's type. That leads to surprises:

```cpp
class Resistor {
public:
    Resistor(double ohms);        // a "converting constructor"
};

void printResistor(const Resistor& r);

printResistor(220.0);   // compiles! 220.0 is silently turned into a Resistor
```

Sometimes that's what you want (a `std::string` is happily built from
`"hello"`). Usually, for your own classes, it isn't — did the caller
mean 220 ohms, 220 kilo-ohms, or did they pass the wrong variable?
Mark single-argument constructors `explicit` to forbid the silent
conversion:

```cpp
class Resistor {
public:
    explicit Resistor(double ohms);
};

printResistor(220.0);            // ERROR - no silent conversion
printResistor(Resistor(220.0));  // OK - the caller said what they meant
```

**Rule of thumb: make every single-argument constructor `explicit`
unless you have a clear reason not to.**

## `const` member functions and `const` objects

A method marked `const` after its parameter list promises **not to
change the object**:

```cpp
class BankAccount {
private:
    double balance = 0;
public:
    double getBalance() const { return balance; }   // promises not to modify
    void deposit(double amount) { balance += amount; }
};
```

The compiler enforces the promise: inside a `const` method, trying to
change a member is a compile error.

Why bother? Because of `const` objects and `const` references — which
you have been using since Module 7 to pass objects efficiently:

```cpp
void printStatement(const BankAccount& account) {
    std::cout << account.getBalance();   // OK - getBalance is const
    account.deposit(10);                 // ERROR - deposit isn't const
}
```

Through a `const` reference you may only call `const` methods. If you
forget to mark `getBalance()` as `const`, then *nobody* holding a
`const BankAccount&` can read the balance — even though reading it is
perfectly safe. This is called **const correctness**:

- Every method that doesn't change the object should be `const`.
- Pass objects you only read as `const T&`.

Getting this right early saves a lot of pain: adding `const` to an
existing large program later tends to ripple through hundreds of
functions.

## Invariants: design behaviour, not just getters and setters

A **class invariant** is a rule that must be true for every object of
the class, at all times between method calls. For example:

- A `BankAccount`'s balance is never negative.
- A `Student`'s scores are all between 0 and 100.
- A `Patient`'s folder number is never empty.

The class's job is to make it **impossible** to break its invariants
from outside. The constructor establishes them; every public method
preserves them.

The most common way beginners accidentally break this is by writing a
getter and setter for every member:

```cpp
class BankAccount {
private:
    double balance;
public:
    double getBalance() const { return balance; }
    void setBalance(double b) { balance = b; }   // anyone can set ANY value
};
```

`balance` is `private`, but `setBalance` makes it effectively public —
`account.setBalance(-5000)` is allowed. The class protects nothing.

Better: ask **what the outside world actually needs to do**, and offer
those operations, each enforcing the rules:

```cpp
class BankAccount {
private:
    double balance = 0;
public:
    double getBalance() const { return balance; }
    bool deposit(double amount) {
        if (amount <= 0) return false;
        balance += amount;
        return true;
    }
    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) return false;
        balance -= amount;
        return true;
    }
};
```

This is sometimes summarised as **"tell, don't ask"**: rather than
asking an object for its data, doing the work yourself, and setting the
result back, *tell* the object what you want and let it do the work
under its own rules. Getters are fine where reading is genuinely
useful; setters should be rare and should always validate.

## `static` members — belonging to the class itself

Normally each object has its own copy of every member variable. A
`static` member is different: there is **exactly one**, shared by the
whole class, existing even when no objects do.

```cpp
class Student {
private:
    static int nextId;      // ONE counter shared by every Student
    int id;
    std::string name;
public:
    Student(std::string n) : id(nextId), name(n) {
        nextId++;
    }
    int getId() const { return id; }

    static int studentsCreated() {   // a static method
        return nextId - 1;
    }
};

int Student::nextId = 1;   // a static data member is defined ONCE, outside the class
```

- A **static data member** is declared inside the class and (for a
  non-`const` one like this) defined once outside it. *(Since C++17
  you can instead write `inline static int nextId = 1;` inside the
  class. Both forms are common in real code; this course uses the
  outside definition so you recognise it.)*
- A **static method** has no `this` — it isn't called on any object —
  so it can only use static members. Call it through the class name:
  `Student::studentsCreated()`.

Typical uses: ID counters, counting how many objects exist, and
constants shared by every object (`static const int MAX_SCORE = 100;`).

## `mutable` — a brief note

Occasionally a `const` method needs to change some *internal* detail
that isn't part of the object's visible state — the classic example is
a cache:

```cpp
class Report {
private:
    std::vector<double> values;
    mutable bool cacheValid = false;
    mutable double cachedAverage = 0;
public:
    double average() const {
        if (!cacheValid) {
            // ... compute, then store it ...
            cacheValid = true;   // allowed because it's mutable
        }
        return cachedAverage;
    }
};
```

`mutable` says "this member may change even in a `const` method". Use
it rarely, and only for things the user of the class can't observe.
If you find yourself making ordinary data `mutable` to silence errors,
the method shouldn't be `const`.

## Defining member functions outside the class

So far you've written every method body inside the class. You can also
**declare** a method inside the class and **define** it outside, using
the class name and the **scope resolution operator** `::`:

```cpp
class Thermostat {
private:
    double targetCelsius = 24.0;
public:
    void setTarget(double celsius);        // declaration only
    double getTarget() const;              // const is part of the signature
};

void Thermostat::setTarget(double celsius) {   // definition
    if (celsius >= 16 && celsius <= 30) {
        targetCelsius = celsius;
    }
}

double Thermostat::getTarget() const {        // repeat const here too
    return targetCelsius;
}
```

`Thermostat::setTarget` means "the `setTarget` that belongs to
`Thermostat`". Keeping the class body short — just declarations —
makes it read like a **table of contents** for the class. It's also
exactly what you'll need in Module 22, where the declarations move into
a header file and the definitions into a separate `.cpp` file.

## Common beginner mistakes

- Assigning members in the constructor body instead of initialising
  them — and then failing to compile when a member is `const` or a
  reference.
- Writing an initializer list in a different order from the member
  declarations (read the `-Wreorder` warning!).
- Leaving `int`/`double`/`bool`/pointer members uninitialised. Give
  them a default member value.
- Forgetting `const` on methods that only read, then being unable to
  call them through a `const&`.
- Forgetting to repeat `const` on an out-of-class definition
  (`double Thermostat::getTarget() const`) — without it, it's a
  different function and won't compile.
- A public setter for every private member — the data is private in
  name only.
- Forgetting to define a static data member outside the class, giving a
  linker error like `undefined reference to Student::nextId`.
- Trying to use `this` or a non-static member inside a static method.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — continue the track
   you chose in Module 20.
4. Commit:

   ```bash
   git add 21-class-design
   git commit -m "Complete Module 21: class design in depth"
   git push
   ```

Next: **[Module 22 — Multi-File Projects & Namespaces](../22-multi-file-projects/README.md)**.
