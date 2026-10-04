# Module 23 — Object Lifetime, Destructors & RAII

Every object you create is **born** (its constructor runs) and, at some
point, **dies**. So far you've thought carefully about birth —
constructors, initializer lists, invariants. This module is about the
other end: **when exactly does an object die, and what happens when it
does?**

The answer leads to the single most important idea in C++ resource
management, with an unfortunately clumsy name: **RAII**. Once you
understand it, you'll see it everywhere in the standard library — and
you'll understand *why* modern C++ code almost never needs to call
`delete`.

This module covers:

- the three kinds of object lifetime: automatic, dynamic, and static
- **destructors** — code that runs automatically when an object dies
- the precise **order** in which objects are constructed and destroyed
- **RAII**: tying a resource to an object's lifetime
- why RAII makes code safe even with early `return`s

## Three kinds of lifetime

### Automatic lifetime (the "stack")

A variable declared inside a function or block lives until the end of
that **block** — the closing `}`:

```cpp
void example() {
    Sensor a("A");          // a is born here
    if (true) {
        Sensor b("B");      // b is born here
    }                       // b dies here - end of its block
    std::cout << "...";
}                           // a dies here - end of the function
```

This is **automatic** lifetime: you never have to do anything to clean
these objects up. They live in a region of memory called **the stack**,
and they are destroyed automatically, every time, when their scope
ends — whether the function finishes normally, `return`s early, or
(Module 31) an exception passes through.

### Dynamic lifetime (the "heap")

An object created with `new` lives until someone calls `delete` on it
— no matter how many scopes end in between (Module 10):

```cpp
Sensor* p = new Sensor("C");   // born
// ... any number of functions and blocks later ...
delete p;                       // dies - only when YOU say so
```

This is **dynamic** lifetime. It's flexible — the object can outlive
the function that created it — but it's also the source of the classic
bugs from Module 10: forget the `delete` and you have a **leak**;
`delete` twice and you have a crash or worse.

### Static lifetime

Global variables and `static` data members (Module 21) are created
before `main` starts and destroyed after `main` ends. You won't need to
think about these much; just know they exist.

## Destructors

A **destructor** is a special member function that runs **automatically
when an object dies**. Its name is the class name with a tilde (`~`) in
front, and it takes no parameters and returns nothing:

```cpp
class Sensor {
private:
    std::string name;
public:
    explicit Sensor(std::string n) : name(n) {
        std::cout << "Sensor " << name << " switched on" << std::endl;
    }

    ~Sensor() {
        std::cout << "Sensor " << name << " switched off" << std::endl;
    }
};
```

Rules:

- A class has **exactly one** destructor. You can't overload it, and
  you never pass it arguments.
- You (almost) **never call a destructor yourself**. It runs
  automatically: at the end of the scope for an automatic object, or
  inside `delete` for a dynamic one.
- If you don't write one, the compiler writes one for you that simply
  destroys each member. For most classes that's exactly right.
- Destructors must not fail. Module 31 explains why, and what that
  means for exceptions; for now, keep destructors simple.

You've already seen `virtual ~Component() {}` in Module 12 — a
destructor that does nothing itself, but is marked `virtual` so that
`delete basePointer;` runs the *derived* class's destructor too. That
rule still holds: **a class meant to be a polymorphic base needs a
virtual destructor.**

Run [`examples/01_tracing_lifetime.cpp`](examples/01_tracing_lifetime.cpp).
Before running it, **predict** every line of output. Printing from
constructors and destructors like this ("tracing") is the best way to
build an accurate mental picture of lifetimes.

## Order of construction and destruction

C++ is very precise about order, and the rule is always the same
shape: **things are destroyed in the reverse order they were
constructed.** Think of a stack of plates: the last plate put on top is
the first one taken off.

- **Local variables in a block:** constructed top to bottom, destroyed
  bottom to top.
- **Members of a class:** constructed in declaration order (Module 21),
  *before* the constructor body runs. Destroyed in reverse order,
  *after* the destructor body runs. So inside your destructor, every
  member is still alive and usable.
- **Base and derived classes (Module 11):** the base part is
  constructed first, then the derived part. Destruction is the reverse:
  the derived destructor runs first, then the base destructor.
- **Elements of a `std::vector`:** destroyed when the vector itself is
  destroyed (or when they're erased).

Why reverse order? Because later things may depend on earlier things.
A `Robot` whose `Motor` member was constructed first may use the motor
in its own constructor; when the robot is destroyed, the robot's own
destructor body runs *first*, while the motor is still alive to be
switched off safely.

[`examples/02_construction_order.cpp`](examples/02_construction_order.cpp)
traces members, base classes, and derived classes together.

## Temporaries

Some objects have no name at all:

```cpp
printReading(Sensor("Temporary"));
```

`Sensor("Temporary")` creates a **temporary** object. It lives until
the end of the **full expression** it was created in — roughly, until
the semicolon — and is then destroyed. Remember temporaries: they
become very important in Module 25 (Move Semantics).

## Heap objects only die when deleted

[`examples/03_heap_lifetime.cpp`](examples/03_heap_lifetime.cpp)
creates objects with `new` inside a function and shows that they
**survive** the end of that function — and that their destructor runs
only when `delete` is called. If `delete` is never called, the
destructor **never runs at all**. A leak isn't just "some memory is
wasted": every bit of cleanup in that destructor (closing a file,
switching off a motor, saving data) silently never happens.

## RAII — Resource Acquisition Is Initialization

A **resource** is anything your program has to *acquire* and then
*give back*:

- memory from `new` (must be `delete`d)
- an open file (must be closed)
- a network connection, a hardware device, a lock, a database
  transaction...
- even "a motor that has been switched on" (must be switched off)

The trouble with resources is the giving-back part. It's easy to write:

```cpp
void logReadings() {
    Motor* m = new Motor();
    m->start();
    if (batteryLow()) {
        return;          // OOPS: the motor is never stopped or deleted
    }
    // ... work ...
    m->stop();
    delete m;
}
```

Every early `return` (and later, every exception) is another path where
the cleanup must be remembered. In a long function with five exit
points, someone will forget one.

**RAII** is the fix. The idea:

1. Wrap the resource in a small class.
2. **Acquire** the resource in the **constructor**.
3. **Release** it in the **destructor**.
4. Create the wrapper as an **automatic** (stack) object.

Because automatic objects are *always* destroyed when their scope ends
— on every path out — the resource is *always* released. You can't
forget, because there's nothing to remember.

```cpp
class MotorSession {
private:
    Motor& motor;
public:
    explicit MotorSession(Motor& m) : motor(m) {
        motor.start();            // acquire
    }
    ~MotorSession() {
        motor.stop();             // release - runs on EVERY exit path
    }
};

void logReadings(Motor& m) {
    MotorSession session(m);      // motor starts here
    if (batteryLow()) {
        return;                   // motor stops automatically
    }
    // ... work ...
}                                 // motor stops automatically here too
```

The name "Resource Acquisition Is Initialization" refers to step 2:
getting the resource *is* initialising the object. Many people find
"**Scope-Bound Resource Management**" a clearer name — the resource is
bound to a scope. Use whichever helps you remember it.

### You have been using RAII all along

- `std::vector` allocates memory in its constructor/`push_back` and
  frees it in its destructor. That's why you never `delete` a vector's
  contents.
- `std::string` does the same for its characters.
- `std::ofstream` and `std::ifstream` (Module 14) open a file in their
  constructor and **close it in their destructor** — which is why
  Module 14 said calling `.close()` yourself is optional.

The standard library is built on RAII. Module 26 adds the most
important RAII classes of all — **smart pointers** — which do for
`new`/`delete` what `MotorSession` does for `start`/`stop`.

[`examples/04_raii_logger.cpp`](examples/04_raii_logger.cpp) builds a
small RAII class that writes a log file, and
[`examples/05_raii_early_return.cpp`](examples/05_raii_early_return.cpp)
compares a manual-cleanup function with an RAII version across several
early-return paths.

## A warning that leads into Module 24

Look at this RAII class, which owns some heap memory:

```cpp
class SampleBuffer {
private:
    double* data;
    int size;
public:
    explicit SampleBuffer(int n) : data(new double[n]), size(n) {}
    ~SampleBuffer() { delete[] data; }
};
```

It looks perfect: memory is acquired in the constructor and released in
the destructor. But try **copying** it:

```cpp
SampleBuffer a(100);
SampleBuffer b = a;   // compiles... and is a serious bug
```

Both `a` and `b` now hold the *same* `data` pointer. When they die,
**both** destructors call `delete[]` on it — a double delete. For now,
**do not copy objects that own a raw resource.** Module 24 explains
exactly what's happening and how to fix it properly.

## Common beginner mistakes

- Calling a destructor by hand (`s.~Sensor();`). Let the language do
  it — calling it yourself means it runs twice.
- Expecting a heap object's destructor to run at the end of a scope.
  Only automatic objects die at `}`; heap objects die at `delete`.
- Forgetting that member objects are still alive inside the destructor
  body (they are!) — or, conversely, using a member that was declared
  *later* in the class from an *earlier* member's constructor.
- Writing cleanup code at the bottom of a function and hoping every
  path reaches it. Put cleanup in a destructor instead.
- Forgetting `virtual` on the destructor of a polymorphic base class
  (Module 12) — the derived part's destructor then never runs.
- Copying an object that owns a raw resource (see above) — wait for
  Module 24.

## Try it yourself

1. Work through [`examples/`](examples/). For every example, predict
   the output **before** you run it.
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md), continuing your
   track.
4. Commit:

   ```bash
   git add 23-object-lifetime-raii
   git commit -m "Complete Module 23: object lifetime, destructors and RAII"
   git push
   ```

Next: **[Module 24 — Copy Semantics](../24-copy-semantics/README.md)**.
