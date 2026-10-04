# Module 28 — Advanced Inheritance

Module 11 taught the core of inheritance: `class Derived : public Base`,
`protected`, overriding, and calling the base constructor. Module 12
added `virtual`. Module 27 then warned you *not* to reach for
inheritance when composition fits better.

So when you *do* use inheritance, you should use it well. This module
fills in the parts of inheritance that Module 11 deliberately skipped:

- **public, protected and private inheritance** — and why you'll
  almost always use `public`
- **inheriting constructors** with `using Base::Base;`
- **name hiding** — the surprising way a derived method can make base
  methods disappear, and how to fix it with `using`
- **`final`** — stopping further overriding or deriving
- **object slicing**, revisited, and how to prevent it
- **multiple inheritance** — a class with two (or more) base classes
- the **diamond problem**, and **virtual inheritance**
- guidelines for when multiple inheritance is (and isn't) a good idea

## public, protected, and private inheritance

You've always written `public` in `class Resistor : public Component`.
That word controls how the **base class's members appear from the
outside of the derived class**:

| Base member is... | `: public Base` | `: protected Base` | `: private Base` |
|---|---|---|---|
| `public` | stays `public` | becomes `protected` | becomes `private` |
| `protected` | stays `protected` | stays `protected` | becomes `private` |
| `private` | inaccessible | inaccessible | inaccessible |

(A base's `private` members are never accessible to the derived class,
whatever the inheritance mode — that hasn't changed since Module 11.)

What this means in practice:

- **Public inheritance** means "**is-a**". Everything a `Component` can
  do publicly, a `Resistor` can do publicly too, and a `Resistor` can be
  used anywhere a `Component&` or `Component*` is expected. This is the
  only mode that allows that conversion from outside the class, so it's
  the only one that works with polymorphism.
- **Private inheritance** means "**is implemented in terms of**". The
  derived class uses the base's code internally, but *nobody outside*
  can see the base's members or treat the derived object as a base
  object.

```cpp
class Timer {
public:
    void start();
    double elapsedSeconds() const;
};

class LessonClock : private Timer {   // uses Timer internally; is NOT a Timer
public:
    void beginLesson() { start(); }
    bool overrun() const { return elapsedSeconds() > 45 * 60; }
};

LessonClock clock;
clock.beginLesson();     // OK
// clock.start();        // ERROR: start() is private in LessonClock
// Timer& t = clock;     // ERROR: can't treat a LessonClock as a Timer from outside
```

But notice — that's exactly what **composition** (Module 27) gives you,
with less surprise:

```cpp
class LessonClock {
private:
    Timer timer;          // has-a
public:
    void beginLesson() { timer.start(); }
    bool overrun() const { return timer.elapsedSeconds() > 45 * 60; }
};
```

> **Guideline:** use **public** inheritance for genuine is-a
> relationships. For "implemented in terms of", **prefer composition**
> over private inheritance. Protected inheritance is very rare;
> recognise it, but you're unlikely to need it.

[`examples/01_inheritance_access_modes.cpp`](examples/01_inheritance_access_modes.cpp)
shows all three side by side, with the lines that would fail commented
out.

## Inheriting constructors: `using Base::Base;`

Constructors are **not** inherited automatically. If `Component` has a
constructor taking a name and a value, and `Fuse` adds nothing that
needs initialising, you'd still have to write:

```cpp
class Fuse : public Component {
public:
    Fuse(std::string name, double amps) : Component(name, amps) {}   // just forwarding
};
```

With several base constructors, that's a lot of boring forwarding.
Since C++11 you can ask for all of them at once:

```cpp
class Fuse : public Component {
public:
    using Component::Component;   // "Fuse has the same constructors as Component"

    bool blowsAt(double amps) const { return amps > value; }
};

Fuse f("F1", 13.0);   // uses Component's constructor
```

Use it when the derived class adds **behaviour** (methods) but no
**new data that needs initialising**. If the derived class has its own
members, give them default member initializers (Module 21), or write a
constructor yourself.

[`examples/02_inheriting_constructors.cpp`](examples/02_inheriting_constructors.cpp)
shows it in action.

## Name hiding — when base methods disappear

This one surprises almost everyone the first time:

```cpp
class Logger {
public:
    void log(std::string message);
    void log(int code);              // an overload
};

class TimestampLogger : public Logger {
public:
    void log(std::string message);   // "override" just the string version
};

TimestampLogger t;
t.log("started");   // OK - TimestampLogger::log(std::string)
t.log(404);         // ERROR: "no matching function" - Logger::log(int) is hidden!
```

The rule: **declaring a function named `log` in the derived class
hides *every* function named `log` in the base class** — all overloads,
whatever their parameters. When the compiler looks up `t.log`, it
finds the name in `TimestampLogger`, stops looking, and never sees
`Logger::log(int)`.

(This has nothing to do with `virtual`: name hiding happens first, when
the compiler looks up the name, before it thinks about which version to
call.)

The fix is a **using-declaration** that brings the base's overloads
back into the derived class's scope:

```cpp
class TimestampLogger : public Logger {
public:
    using Logger::log;               // un-hide ALL of Logger's log overloads...
    void log(std::string message);   // ...then replace just this one
};

t.log(404);   // OK now - Logger::log(int)
```

[`examples/03_name_hiding.cpp`](examples/03_name_hiding.cpp)
demonstrates the problem and the fix.

## `final` — "no further"

Sometimes a design decision is *finished*. `final` lets you say so, and
the compiler enforces it.

**On a virtual method:** derived classes may not override it any
further.

```cpp
class SafetyDevice {
public:
    virtual ~SafetyDevice() {}
    virtual void emergencyStop() = 0;
};

class CircuitBreaker : public SafetyDevice {
public:
    void emergencyStop() final;      // overrides... and nobody below may change it
};

class SmartBreaker : public CircuitBreaker {
public:
    // void emergencyStop() override;   // ERROR: emergencyStop is final
};
```

**On a class:** nobody may derive from it at all.

```cpp
class Thermistor final : public Sensor {   // a leaf - can't be derived from
    // ...
};

// class FancyThermistor : public Thermistor {};   // ERROR: Thermistor is final
```

Use `final` when deriving or overriding would break an important rule
(a safety behaviour that must not be changed, an invariant a subclass
could violate), or simply to document "this class was not designed to
be a base class". It can also let the compiler make calls slightly
faster, but that's a side benefit — use it for design reasons.

[`examples/04_final.cpp`](examples/04_final.cpp) shows both uses.

## Object slicing, revisited

Module 12 showed slicing when passing a derived object **by value** to
a function taking the base. It happens in two more places:

```cpp
Resistor r(220);
Component c = r;               // 1. initialising a base VARIABLE from a derived object
c = r;                         // 2. ASSIGNING a derived object to a base variable

std::vector<Component> parts;  // 3. a container of base objects BY VALUE
parts.push_back(r);            //    -> stores only the Component part
```

In every case, only the base part is copied, and the derived part is
silently thrown away. A `std::vector<Component>` can never hold a
`Resistor` — only a `Component` that used to be part of one.

Two ways to prevent it:

1. **Use pointers or references for polymorphic objects** — always.
   `std::vector<std::unique_ptr<Component>>` (Module 26) can't slice.
2. **Make polymorphic base classes impossible to copy from outside**,
   so slicing becomes a compile error. A common way is to make the base
   class abstract (it has a pure virtual function, Module 29) — then
   `Component c = r;` can't compile because no plain `Component` can
   exist. Another is to make its copy operations `protected`.

[`examples/05_slicing_revisited.cpp`](examples/05_slicing_revisited.cpp)
shows all three forms of slicing.

## Multiple inheritance

A class can have **more than one** base class:

```cpp
class Camera {
public:
    void takePhoto();
};

class Phone {
public:
    void call(std::string number);
};

class Smartphone : public Camera, public Phone {   // is-a Camera AND is-a Phone
public:
    void shareLastPhoto(std::string number);
};

Smartphone s;
s.takePhoto();          // from Camera
s.call("0302123456");   // from Phone
```

- Base classes are constructed **in the order they're listed** in the
  class declaration (`Camera`, then `Phone`), and destroyed in reverse.
- A `Smartphone` can be used anywhere a `Camera&` **or** a `Phone&` is
  expected.

### Ambiguity

If both bases have a member with the same name, using it is
**ambiguous**, and the compiler refuses to guess:

```cpp
class Camera { public: double batteryLevel() const; };
class Phone  { public: double batteryLevel() const; };

Smartphone s;
s.batteryLevel();          // ERROR: ambiguous - Camera's or Phone's?
s.Camera::batteryLevel();  // OK - qualified with the base class name
```

Usually the better fix is for `Smartphone` to provide its own
`batteryLevel()` that decides what it means for a smartphone.

[`examples/06_multiple_inheritance.cpp`](examples/06_multiple_inheritance.cpp)
shows construction order and resolving an ambiguity.

## The diamond problem

Here's where multiple inheritance gets genuinely tricky:

```
            Device
           /      \
  PoweredDevice   NetworkedDevice
           \      /
           SmartPlug
```

```cpp
class Device {
protected:
    std::string serialNumber;
};
class PoweredDevice   : public Device { /* ... */ };
class NetworkedDevice : public Device { /* ... */ };
class SmartPlug : public PoweredDevice, public NetworkedDevice { /* ... */ };
```

A `SmartPlug` contains a `PoweredDevice`, which contains a `Device`...
**and** a `NetworkedDevice`, which contains **another** `Device`. So
every `SmartPlug` has **two** separate serial numbers. Which one is the
real one? Any use of `serialNumber` inside `SmartPlug` is ambiguous,
and the two copies can drift apart.

### Virtual inheritance

The fix is to declare that the shared base should appear **only once**,
however many paths lead to it:

```cpp
class PoweredDevice   : virtual public Device { /* ... */ };
class NetworkedDevice : virtual public Device { /* ... */ };
class SmartPlug : public PoweredDevice, public NetworkedDevice { /* ... */ };
```

Now a `SmartPlug` contains exactly one `Device`, shared by both paths.

Note this is a completely different use of the word `virtual` from
`virtual` *functions* — same keyword, different meaning.

Virtual inheritance comes with one important rule: **the most-derived
class constructs the virtual base directly**. Because `Device` is
shared, neither `PoweredDevice` nor `NetworkedDevice` can be in charge
of constructing it, so `SmartPlug` must:

```cpp
class SmartPlug : public PoweredDevice, public NetworkedDevice {
public:
    SmartPlug(std::string serial)
        : Device(serial),               // the most-derived class constructs the shared base
          PoweredDevice(serial, 230),   // (their own calls to Device(...) are skipped)
          NetworkedDevice(serial, "192.168.1.20") {}
};
```

[`examples/07_diamond_virtual_inheritance.cpp`](examples/07_diamond_virtual_inheritance.cpp)
shows the diamond with and without virtual inheritance, counting how
many `Device`s each `SmartPlug` really contains.

## When is multiple inheritance a good idea?

Multiple inheritance has a bad reputation, mostly because of the
diamond. Here's the practical guidance used in most professional C++
code:

- ✔ **Inheriting from several *interfaces*** — base classes with only
  pure virtual functions and no data (Module 29) — is common and safe.
  A class can be both `Printable` and `Saveable`. With no data in the
  bases, there's nothing to duplicate.
- ⚠ **Inheriting from several classes *with data*** is occasionally
  useful, but think hard first. Ask whether composition would be
  simpler: does a smartphone *have* a camera, or *is* it one?
- ⚠ **A diamond of classes with data** needs virtual inheritance and
  careful constructors. If you find yourself here, step back and
  reconsider the design.

## Common beginner mistakes

- Leaving out `public` (`class Resistor : Component`) — for a `class`,
  the default is **private** inheritance, so nothing works from outside
  and polymorphism fails with confusing errors.
- Using private inheritance where composition would be clearer.
- Adding an overload in a derived class and being surprised that the
  base overloads "disappeared" — add `using Base::name;`.
- Using `using Base::Base;` when the derived class has its own members
  that need initialising — they'll be left with their default values.
- Storing polymorphic objects by value in a container
  (`std::vector<Base>`) — they're sliced.
- Ambiguous calls with multiple inheritance — qualify them, or better,
  provide your own version in the derived class.
- In a diamond, forgetting `virtual` on **both** middle classes, or
  forgetting that the most-derived class must construct the virtual
  base.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md), continuing your
   track.
4. Commit:

   ```bash
   git add 28-advanced-inheritance
   git commit -m "Complete Module 28: advanced inheritance"
   git push
   ```

Next: **[Module 29 — Abstract Classes, Interfaces & Advanced Polymorphism](../29-abstract-classes-interfaces/README.md)**.
