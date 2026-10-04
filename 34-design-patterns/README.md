# Module 34 — Design Patterns in C++

Module 33 gave you principles for judging a design. This module gives
you a **catalogue of proven designs** to reach for.

A **design pattern** is a named, reusable solution to a problem that
keeps coming up in object-oriented programs. Patterns aren't libraries
you download or code you copy — they're *shapes* of classes and
relationships that experienced programmers recognise. Their real value
is **vocabulary**: when a teammate says "let's make the alarm an
Observer" or "use a Factory for the sensors", everyone instantly knows
the structure they mean.

The classic catalogue (from the 1994 book *Design Patterns* by Gamma,
Helm, Johnson and Vlissides — the "Gang of Four") groups patterns into
three families. This module covers the ten you're most likely to meet:

| Family | Question it answers | Patterns in this module |
|---|---|---|
| **Creational** | How are objects *created*? | Factory, Builder, Singleton |
| **Structural** | How are objects *combined*? | Adapter, Composite, Decorator |
| **Behavioural** | How do objects *communicate and share work*? | Strategy, Observer, State, Command |

It ends with a brief look at **Model–View–Controller (MVC)**, and a
guide to choosing a pattern.

This is the biggest module in Part 3. Take it in two sittings if you
need to: creational and structural first, behavioural second. Every
pattern has a small runnable example — run each one, and for each,
ask: *what change does this pattern make easy?*

---

## Creational patterns

### 1. Factory — "decide which class to create, in one place"

**Problem.** Your program creates objects of a polymorphic hierarchy
from data — a menu choice, a line in a file, a code from a sensor. If
`new Thermistor(...)` / `make_unique<LightSensor>(...)` calls are
scattered all over the program, every new sensor type means hunting
them all down (an OCP violation).

**Solution.** Put the decision in **one function** (or class) that
takes a description and returns a `std::unique_ptr<Base>`:

```cpp
std::unique_ptr<Sensor> makeSensor(const std::string& type, const std::string& id) {
    if (type == "temperature") return std::make_unique<Thermistor>(id);
    if (type == "light")       return std::make_unique<LightSensor>(id);
    if (type == "gas")         return std::make_unique<GasSensor>(id);
    throw std::invalid_argument("unknown sensor type: " + type);
}
```

Yes, there's still an `if` chain — but now it's the **only** one. The
rest of the program works with `Sensor&` and never names a concrete
class. A more extensible variant uses a **registry** (a `std::map` from
names to creation functions) so new types can register themselves
without editing the factory.

**Use it when** objects are created from runtime data, or when you want
calling code to depend only on the base class.
→ [`examples/01_factory.cpp`](examples/01_factory.cpp)

### 2. Builder — "construct a complicated object step by step"

**Problem.** An object has many optional settings. A constructor with
ten parameters (`Robot("Scout", 2, true, false, 30, 5, ...)`) is
unreadable and easy to get wrong — which `true` was "has camera"?

**Solution.** A separate **builder** object with one clearly named
method per setting, each returning the builder itself so calls can be
**chained**, and a final `build()` that validates and creates the
object:

```cpp
Robot scout = RobotBuilder("Scout")
                  .wheels(4)
                  .withCamera()
                  .batteryCapacity(5000)
                  .maxSpeed(1.2)
                  .build();
```

**Use it when** construction has many optional parts or needs
validation across several settings.
→ [`examples/02_builder.cpp`](examples/02_builder.cpp)

### 3. Singleton — "exactly one instance, globally reachable" (use with care)

**Problem.** There should be exactly one of something — one
configuration, one log — and many parts of the program need it.

**Solution.** Make the constructor `private` and provide a `static`
method that returns the one instance:

```cpp
class AppConfig {
public:
    static AppConfig& instance() {
        static AppConfig theOne;   // created the first time this runs; destroyed at program end
        return theOne;
    }
    AppConfig(const AppConfig&) = delete;
    AppConfig& operator=(const AppConfig&) = delete;
private:
    AppConfig() {}                 // nobody else can create one
};

AppConfig::instance().setSchoolName("MakersPlace Academy");
```

(A `static` local variable is created the first time execution reaches
it, and lives until the program ends — so this is safe and simple.)

**Be careful.** Singleton is the most criticised pattern in the book. It
is really a **global variable** in disguise: any code can reach it, so
hidden dependencies spread everywhere, and it makes testing hard (you
can't swap in a fake — Module 33's DIP). Prefer creating one object in
`main` and **passing it** to whoever needs it. Use Singleton only for
genuinely global, rarely-changing things, and recognise it in code you
read.
→ [`examples/03_singleton.cpp`](examples/03_singleton.cpp)

---

## Structural patterns

### 4. Adapter — "make an incompatible interface fit"

**Problem.** You have code written against your interface — say
`TemperatureSensor` with `double celsius()` — and you need to use a
class you **can't change** (from a library, or a supplier's driver)
whose interface is different — say `FahrenheitProbe` with
`int readTenthsOfDegreeF()`.

**Solution.** Write an **adapter** class that implements your interface
by *wrapping* the other object and translating each call:

```cpp
class FahrenheitProbeAdapter : public TemperatureSensor {
    FahrenheitProbe& probe;                       // the adaptee
public:
    explicit FahrenheitProbeAdapter(FahrenheitProbe& p) : probe(p) {}
    double celsius() const override {
        double f = probe.readTenthsOfDegreeF() / 10.0;
        return (f - 32) * 5.0 / 9.0;
    }
};
```

Like a plug adapter for a foreign socket: nothing on either side
changes. **Use it when** integrating third-party or legacy code.
→ [`examples/04_adapter.cpp`](examples/04_adapter.cpp)

### 5. Composite — "treat a group like a single item"

**Problem.** You have a tree-shaped structure — a school made of
departments made of classes; a house made of floors made of rooms made
of appliances — and you want to ask the same question ("how many
students?", "how much power?") of a single item **or** of a whole
group, without caring which it is.

**Solution.** Leaves and groups implement the **same interface**. A
group holds children (as `unique_ptr`s to the interface) and answers by
asking each child:

```cpp
class EnergyNode {                                  // the common interface
public:
    virtual ~EnergyNode() = default;
    virtual double dailyKwh() const = 0;
};

class Appliance : public EnergyNode { /* a leaf: knows its own kWh */ };

class Zone : public EnergyNode {                    // a composite: room, floor, building...
    std::vector<std::unique_ptr<EnergyNode>> children;
public:
    void add(std::unique_ptr<EnergyNode> child);
    double dailyKwh() const override {
        double total = 0;
        for (const auto& c : children) total += c->dailyKwh();   // recursion through the tree
        return total;
    }
};
```

A `Zone` can contain appliances *and other zones*, to any depth.
→ [`examples/05_composite.cpp`](examples/05_composite.cpp)

### 6. Decorator — "add responsibilities by wrapping"

**Problem.** You want to add optional extras to an object — logging,
smoothing, unit conversion, caching — in any combination, without
creating a subclass for every combination (Module 27's "class
explosion").

**Solution.** A **decorator** implements the same interface as the
object it wraps, holds the wrapped object, and adds its own behaviour
before or after delegating to it. Decorators can wrap other decorators:

```cpp
class Sensor { public: virtual ~Sensor() = default; virtual double read() = 0; };

class SensorDecorator : public Sensor {
protected:
    std::unique_ptr<Sensor> inner;
public:
    explicit SensorDecorator(std::unique_ptr<Sensor> s) : inner(std::move(s)) {}
};

class Smoothed : public SensorDecorator { /* averages the last few inner->read() values */ };
class Logged   : public SensorDecorator { /* prints each value, then returns it */ };

auto sensor = std::make_unique<Logged>(
                  std::make_unique<Smoothed>(
                      std::make_unique<NoisyThermistor>()));   // logging + smoothing, in that order
```

**Use it when** you need flexible combinations of extra behaviour.
→ [`examples/06_decorator.cpp`](examples/06_decorator.cpp)

---

## Behavioural patterns

### 7. Strategy — "swap an algorithm at runtime"

**Problem.** One task can be done several ways — grading on a
percentage scale or a GPA scale; charging a flat or time-of-use tariff;
triaging with an adult or paediatric score — and the choice may change
while the program runs.

**Solution.** Put each algorithm in its own class behind a common
interface, and give the object that *uses* it a member pointing to the
current strategy:

```cpp
class GradingScheme {
public:
    virtual ~GradingScheme() = default;
    virtual std::string grade(double percentage) const = 0;
};
class LetterGrades : public GradingScheme { /* A, B, C... */ };
class WassceGrades : public GradingScheme { /* A1, B2, B3... C6, D7, E8, F9 */ };

class ReportCard {
    const GradingScheme* scheme;                       // the current strategy
public:
    void setScheme(const GradingScheme& s) { scheme = &s; }
    void print(double pct) const { std::cout << scheme->grade(pct); }
};
```

You've seen the shape before: Module 33's `PaymentMethod` was a
Strategy. For small strategies, a **lambda** or `std::function` can play
the same role.
→ [`examples/07_strategy.cpp`](examples/07_strategy.cpp)

### 8. Observer — "notify everyone who's interested"

**Problem.** When something happens to one object — a sensor crosses a
threshold, a fee is paid, a patient's score rises — several *other*
objects need to react: a display, a logger, an SMS alert, an alarm. If
the sensor calls each of them directly, it's coupled to all of them,
and adding a new reaction means editing the sensor.

**Solution.** The **subject** keeps a list of **observers** (through an
interface) and notifies all of them when something happens. Observers
**subscribe** and **unsubscribe** themselves; the subject knows nothing
about what they do:

```cpp
class TemperatureObserver {
public:
    virtual ~TemperatureObserver() = default;
    virtual void onTemperature(double celsius) = 0;
};

class TemperatureSensor {
    std::vector<TemperatureObserver*> observers;      // non-owning (Module 27: association)
public:
    void subscribe(TemperatureObserver& o)   { observers.push_back(&o); }
    void unsubscribe(TemperatureObserver& o);
    void newReading(double c) {
        for (TemperatureObserver* o : observers) o->onTemperature(c);
    }
};
```

**Lifetime warning:** the subject holds raw pointers to observers, so an
observer must **unsubscribe before it is destroyed** (an RAII
destructor is a good place), or be guaranteed to outlive the subject.
→ [`examples/08_observer.cpp`](examples/08_observer.cpp)

### 9. State — "behaviour that depends on the current mode"

**Problem.** An object behaves differently depending on its **mode** —
an infusion pump that is *idle*, *running*, *paused*, or *alarming*; a
traffic light; a robot that is *charging*, *exploring*, or *returning*.
Writing every method as a `switch` on the current mode becomes a mess
as modes and events multiply.

**Solution.** Make each mode a **class** implementing a common
`State` interface, with one method per event. The object holds a
pointer to its current state object and delegates events to it; a state
can switch the object to a different state:

```cpp
class PumpState {
public:
    virtual ~PumpState() = default;
    virtual void pressStart(InfusionPump& pump) = 0;
    virtual void pressStop(InfusionPump& pump) = 0;
    virtual void occlusion(InfusionPump& pump) = 0;
    virtual std::string name() const = 0;
};

class IdleState : public PumpState {
    void pressStart(InfusionPump& pump) override { pump.setState(std::make_unique<RunningState>()); }
    // ...
};
```

Each state's rules live together in one small class, and an invalid
event in a given state simply does nothing (or warns).
→ [`examples/09_state.cpp`](examples/09_state.cpp)

### 10. Command — "turn a request into an object"

**Problem.** You want to queue actions, schedule them, log them, or
**undo** them — "switch on the fan", "set thermostat to 22 °C",
"enrol Ama in Robotics". A plain function call happens and is gone.

**Solution.** Represent each request as an **object** with `execute()`
(and, for undo, `undo()`):

```cpp
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual std::string describe() const = 0;
};

class SetThermostat : public Command {
    Thermostat& t; double newTarget; double oldTarget = 0;
public:
    void execute() override { oldTarget = t.target(); t.setTarget(newTarget); }
    void undo() override    { t.setTarget(oldTarget); }
};
```

An **invoker** (a remote control, a scheduler, a menu) runs commands and
keeps a history stack — so "undo" is simply "pop the last command and
call `undo()`".
→ [`examples/10_command.cpp`](examples/10_command.cpp)

---

## A brief look at Model–View–Controller (MVC)

Patterns combine into **architectures**. The most famous is **MVC**,
used by many apps with a user interface:

- **Model** — the data and the rules (your `Gradebook`, `Ward`,
  `EnergyMeter`). Knows nothing about screens or keyboards.
- **View** — displays the model (a console table, a web page, a phone
  screen). Often an **Observer** of the model, redrawing when it
  changes.
- **Controller** — turns user input into actions on the model (often
  **Commands**).

The point is SRP at the scale of a whole program: you can add a phone
app *View* to a school system without touching the grading *Model*.

## Choosing a pattern

| If you need to... | Consider |
|---|---|
| create objects from runtime data without naming concrete classes everywhere | **Factory** |
| create an object with many optional settings, readably | **Builder** |
| guarantee exactly one instance (think twice!) | **Singleton** |
| use a class whose interface doesn't match yours | **Adapter** |
| treat single items and groups of items the same way | **Composite** |
| add optional extras in flexible combinations | **Decorator** |
| choose between interchangeable algorithms, maybe at runtime | **Strategy** |
| let many objects react to events from one object | **Observer** |
| change behaviour depending on an object's mode | **State** |
| queue, schedule, log or undo actions | **Command** |

> **Patterns are tools, not goals.** Don't start a design by asking
> "where can I use a pattern?". Start with the problem; if it matches
> one of the situations in the table, the pattern gives you a proven
> shape — and a name to explain it with. A program with a pattern in
> every class is as hard to read as one with none.

## Common beginner mistakes

- Using Singleton as a convenient global variable for everything.
- Observers that are destroyed without unsubscribing — the subject is
  left holding dangling pointers.
- Confusing **Strategy** and **State**: both swap an object behind an
  interface, but a strategy is usually *chosen from outside*, while
  states *switch themselves* in response to events.
- Confusing **Decorator** and **Adapter**: a decorator keeps the *same*
  interface and adds behaviour; an adapter *changes* the interface.
- A Composite whose leaf classes are forced to implement "add child"
  methods (breaking ISP/LSP) — keep child management on the group class.
- Forcing a pattern onto a problem that doesn't need it.

## Try it yourself

1. Work through all ten [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md), continuing your
   track.
4. Commit:

   ```bash
   git add 34-design-patterns
   git commit -m "Complete Module 34: design patterns"
   git push
   ```

Next: **[Module 35 — Testing & Debugging OO Code](../35-testing-debugging/README.md)**.
