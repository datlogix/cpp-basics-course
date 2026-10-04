# Module 33 — SOLID Principles & Clean Design

You now know essentially every object-oriented feature C++ offers:
classes, invariants, lifetimes, copying and moving, ownership,
relationships, inheritance in all its forms, interfaces, operators,
exceptions, and templates. The remaining question isn't *"how do I
write this?"* but *"how should I **organise** this so it's still easy
to change in a year?"*

Experienced programmers have distilled their answer into five
principles, known by the acronym **SOLID**:

- **S** — Single Responsibility Principle
- **O** — Open/Closed Principle
- **L** — Liskov Substitution Principle
- **I** — Interface Segregation Principle
- **D** — Dependency Inversion Principle

Along the way this module covers the ideas underneath all five —
**coupling** and **cohesion** — plus a catalogue of common **code
smells** and a safe way to **refactor**.

These are principles, not laws. Each one is a question to ask about a
design. Applied blindly, they can make code *more* complicated; applied
with judgement, they're the difference between code you can extend
calmly and code everyone is afraid to touch.

## Why bother? The cost of change

Most of the effort in real software isn't writing it — it's
**changing** it: new features, new rules, fixes, new hardware. A design
is good if changes are:

- **local** — one change touches one place, not twenty;
- **safe** — changing one thing doesn't silently break another;
- **additive** — new features mostly add new code rather than editing
  old, tested code.

Every SOLID principle is a way of getting one of those properties.

## Coupling and cohesion

Two words appear in almost every discussion of design:

- **Cohesion** is how closely the things *inside* one class belong
  together. A `FeeAccount` whose methods are all about fees and
  payments is **highly cohesive**. A class that records payments *and*
  formats PDF timetables *and* sends SMS messages has **low cohesion**.
- **Coupling** is how much one class depends on the *details* of
  another. If changing how `Gradebook` stores scores forces changes in
  ten other classes, they're **tightly coupled**. If those classes only
  use `Gradebook`'s public methods, they're **loosely coupled**.

> **Aim for high cohesion and low coupling.** Each class should do one
> coherent job, and know as little as possible about how the others do
> theirs.

You've been practising this all along: encapsulation (Module 8),
"tell, don't ask" (Module 21), composition (Module 27), and programming
to interfaces (Module 29) are all ways of reducing coupling.

## S — the Single Responsibility Principle

> **A class should have one reason to change.**

"Responsibility" here means a *reason the code might need to change* —
usually tied to one group of people or one kind of requirement.

```cpp
class ReportCard {                      // BEFORE: three responsibilities
public:
    double average() const;             // 1. grading rules     (changes when the school changes its policy)
    std::string toHtml() const;         // 2. presentation      (changes when the design changes)
    void saveToFile(std::string) const; // 3. storage           (changes when we move to a database)
};
```

Three different groups of people could ask for changes to this one
class, for three unrelated reasons — and every change risks breaking
the other two jobs. Split it:

```cpp
class ReportCard { public: double average() const; /* grading only */ };
class ReportCardFormatter { public: std::string toHtml(const ReportCard&) const; };
class ReportCardRepository { public: void save(const ReportCard&); };
```

Now each class has one reason to change, and each is small enough to
understand and test on its own.

**Watch out for over-applying it.** SRP doesn't mean "one method per
class". A `FeeAccount` that records payments *and* calculates the
balance has one responsibility — managing a fee account — even though
it has several methods.

[`examples/01_srp.cpp`](examples/01_srp.cpp) shows a before and after.

## O — the Open/Closed Principle

> **Software should be open for extension, but closed for
> modification.**

You should be able to add new behaviour **without editing** existing,
working code. The classic violation is a `switch` (or `if` chain) on a
type code:

```cpp
double monthlyCost(const Appliance& a) {            // BEFORE
    switch (a.type) {
        case FRIDGE:          return a.watts * 24 * 30 / 1000.0 * tariff;
        case TELEVISION:      return a.watts * a.hours * 30 / 1000.0 * tariff;
        case AIR_CONDITIONER: return a.watts * a.hours * a.duty * 30 / 1000.0 * tariff;
    }
}
```

Every new kind of appliance means **editing** this function — and
every other `switch` like it, scattered across the program. Miss one,
and you have a bug.

With polymorphism (Modules 12 and 29), each appliance knows its own
behaviour, and new kinds are **added**, not edited in:

```cpp
class Appliance { public: virtual double dailyKwh() const = 0; };
class Fridge : public Appliance { /* ... */ };
class WaterHeater : public Appliance { /* new - nothing else changes */ };

double monthlyCost(const Appliance& a) { return a.dailyKwh() * 30 * tariff; }   // closed for modification
```

Templates (Module 32) and the Strategy pattern (Module 34) are other
ways of achieving the same thing.

[`examples/02_ocp.cpp`](examples/02_ocp.cpp) shows the switch version
and the extensible version side by side.

## L — the Liskov Substitution Principle

> **Objects of a derived class must be usable anywhere the base class
> is expected, without the program behaving incorrectly.**

Named after computer scientist Barbara Liskov. It's the rule that makes
"is-a" (Module 11) honest. If code works with a `Base&`, it must keep
working — *correctly*, not just compiling — when given any `Derived`.

The famous trap:

```cpp
class Rectangle {
public:
    virtual void setWidth(double w)  { width = w; }
    virtual void setHeight(double h) { height = h; }
    double area() const { return width * height; }
protected:
    double width = 0, height = 0;
};

class Square : public Rectangle {          // "a square IS-A rectangle"... in maths
public:
    void setWidth(double w) override  { width = height = w; }
    void setHeight(double h) override { width = height = h; }
};

void stretch(Rectangle& r) {
    r.setWidth(4);
    r.setHeight(5);
    assert(r.area() == 20);    // true for every Rectangle... FALSE for a Square (25)
}
```

(`assert`, from `<cassert>`, stops the program with an error message if
its condition is false — Module 35 uses it for testing.)

`Square` compiles fine and overrides correctly, but it breaks a promise
that `Rectangle` made — "setting the width doesn't change the height" —
so code written for rectangles misbehaves. In maths a square is a
rectangle; in *this program*, with *these operations*, it isn't.

Signs you're breaking LSP:

- a derived class **throws** "not supported" from a method the base
  promised (a `Penguin` whose `fly()` throws);
- a derived class **strengthens the rules** — accepts fewer inputs than
  the base (a `SafeAccount` whose `withdraw` rejects amounts the base
  allowed);
- a derived class **weakens the guarantees** — produces results the
  base promised it wouldn't;
- calling code needs `dynamic_cast` (Module 29) to treat one subclass
  specially.

The fix is almost always to **rethink the hierarchy** — e.g. separate
`Shape` subclasses with no setters, or a `FlyingBird` interface that
only flying birds implement.

[`examples/03_lsp.cpp`](examples/03_lsp.cpp) demonstrates the problem
and a fix.

## I — the Interface Segregation Principle

> **No class should be forced to depend on methods it doesn't use.**

A "fat" interface makes every implementer provide everything:

```cpp
class SmartDevice {                       // BEFORE: one fat interface
public:
    virtual void switchOn() = 0;
    virtual void switchOff() = 0;
    virtual double readTemperature() = 0;
    virtual void setBrightness(int) = 0;
    virtual void lock() = 0;
};

class SmartBulb : public SmartDevice {
    // ...forced to implement readTemperature() and lock() - which make no sense for a bulb
};
```

Implementers end up writing empty or throwing methods (which, as you
just saw, also breaks LSP). Users of the interface depend on far more
than they need.

Split it into small, focused interfaces (Module 29), and let each class
implement only the ones that apply:

```cpp
class Switchable  { public: virtual void switchOn() = 0; virtual void switchOff() = 0; /* + virtual dtor */ };
class Dimmable    { public: virtual void setBrightness(int) = 0; };
class TempSensing { public: virtual double readTemperature() = 0; };
class Lockable    { public: virtual void lock() = 0; };

class SmartBulb : public Switchable, public Dimmable { /* only what it really does */ };
class SmartLock : public Lockable { /* ... */ };
class Thermostat : public Switchable, public TempSensing { /* ... */ };
```

[`examples/04_isp.cpp`](examples/04_isp.cpp) shows the split.

## D — the Dependency Inversion Principle

> **High-level code should not depend on low-level details. Both should
> depend on abstractions.**

"High-level" code is the important business logic — *what the program
is for*. "Low-level" code is the details of *how*: which file format,
which SMS provider, which sensor model.

```cpp
class FeeReminderService {               // BEFORE: high-level...
private:
    BulkSmsGateway sms;                // ...welded to ONE low-level SMS provider
public:
    void remindDebtors(const Ledger& ledger);
};
```

To switch SMS provider, send by email instead, or **test** the
reminder logic without sending real messages, you'd have to edit
`FeeReminderService`. The dependency arrow points from important code
to an unimportant detail.

Invert it: introduce an **abstraction** (an interface) that the
high-level code owns, and make the detail implement it:

```cpp
class MessageSender {                    // the abstraction
public:
    virtual ~MessageSender() = default;
    virtual void send(const std::string& to, const std::string& text) = 0;
};

class FeeReminderService {
private:
    MessageSender& sender;               // depends only on the abstraction
public:
    explicit FeeReminderService(MessageSender& s) : sender(s) {}   // "dependency injection"
    void remindDebtors(const Ledger& ledger);
};

class SmsSender   : public MessageSender { /* real SMS */ };
class EmailSender : public MessageSender { /* real email */ };
class FakeSender  : public MessageSender { /* records messages - for testing (Module 35) */ };
```

Passing the dependency in through the constructor, instead of the class
creating it itself, is called **dependency injection**. It's the single
most useful technique for making code testable, and Module 35 builds on
it directly.

[`examples/05_dip.cpp`](examples/05_dip.cpp) shows the before and
after, with a fake sender.

## Code smells

A **code smell** is a surface sign that a design *might* have a deeper
problem. Learn to notice them:

| Smell | What it looks like | Often fixed by |
|---|---|---|
| **God class** | One huge class that knows and does everything | SRP: split by responsibility |
| **Long method** | A function you have to scroll to read | Extract smaller, well-named functions |
| **Switch on type** | `switch (kind)` / `if (type == ...)` chains, especially repeated | OCP: polymorphism, or Strategy |
| **Duplicated code** | The same logic copy-pasted in several places | Extract a function or class |
| **Feature envy** | A method that mostly uses *another* object's data | Move the method to that class ("tell, don't ask") |
| **Primitive obsession** | Money as `double`, IDs as bare `std::string`, units as plain numbers | A small value type (Module 30) |
| **Long parameter list** | `f(a, b, c, d, e, f, g)` | Group parameters into a struct or class |
| **Refused bequest** | A subclass ignores or overrides-to-nothing what it inherits | LSP: fix the hierarchy |
| **Shotgun surgery** | One small change needs edits in many classes | Bring the scattered logic together (cohesion) |
| **Comments explaining confusing code** | `// add 5 if the thing is the other thing` | Rename and restructure so the code explains itself |

## Refactoring safely

**Refactoring** means improving the structure of code **without
changing what it does**. The safe way:

1. **Have a way to check behaviour.** Before changing anything, save
   the program's output for a set of inputs (or, better, write tests —
   Module 35).
2. **Take small steps.** Extract one function, rename one variable,
   move one method. Compile and check after **each** step.
3. **Commit after each successful step** (`git commit`), so you can
   always go back.
4. **Never mix refactoring with adding features.** First make the
   change easy (refactor), *then* make the easy change (feature) — in
   separate commits.

## Common beginner mistakes

- Treating SOLID as rules to apply everywhere, producing dozens of tiny
  interfaces and classes for a 200-line program. Apply a principle when
  you can name the change it protects you from.
- Reading SRP as "one method per class".
- Building inheritance on real-world "is-a" (a square is a rectangle)
  rather than on **behaviour** — that's how LSP gets broken.
- Creating an interface with only one implementation and no plan for
  a second (or for tests) — an abstraction that adds reading effort
  and buys nothing.
- Having classes create their own dependencies (`BulkSmsGateway sms;`)
  instead of receiving them, making them impossible to test in
  isolation.
- Refactoring and adding features in the same step, so when something
  breaks you can't tell which change caused it.

## Try it yourself

1. Work through [`examples/`](examples/). Each one has a `before` and
   an `after` namespace in one file — read both.
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md), continuing your
   track — this one is a **refactoring** project.
4. Commit:

   ```bash
   git add 33-solid-principles
   git commit -m "Complete Module 33: SOLID principles and clean design"
   git push
   ```

Next: **[Module 34 — Design Patterns in C++](../34-design-patterns/README.md)**.
