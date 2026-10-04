# Module 26 — Smart Pointers & Ownership

Module 10 taught you `new` and `delete`, and ended with "a brief,
honest note on smart pointers": they're the recommended default in real
code, and understanding raw pointers first is what makes them make
sense. Modules 23–25 gave you that understanding — RAII, copying, and
moving. Now you're ready.

A **smart pointer** is an RAII class that owns a heap object and
`delete`s it automatically in its destructor. That's all — but it
changes how you write C++. After this module, you should essentially
**never write `delete` in new code again**.

This module covers:

- **ownership** — the question every pointer must answer
- **`std::unique_ptr`** and `std::make_unique` — sole ownership
- transferring ownership (moving) vs **borrowing** (raw pointers and
  references)
- smart pointers in **polymorphic containers** — fixing Part 2's
  `vector<Base*>` for good
- **`std::shared_ptr`** and `std::make_shared` — shared ownership
- **`std::weak_ptr`** — observing without owning, and breaking cycles
- guidelines for choosing between them

All three smart pointers live in the `<memory>` header.

## The real question: who owns this?

Look at this function signature:

```cpp
Sensor* createSensor(std::string name);
```

It returns a raw pointer. Must the caller `delete` it? Or does some
other object keep it and delete it later? Is it even a heap object? The
signature can't tell you. You have to read documentation (if any) or
the function's code — and if you guess wrong, you get a leak or a
double delete.

That's the core problem with raw owning pointers: **ownership is
invisible**. The **owner** of a heap object is whoever is responsible
for deleting it. Smart pointers make ownership **part of the type**, so
the compiler can see it — and enforce it.

## `std::unique_ptr` — exactly one owner

A `std::unique_ptr<T>` owns one heap object of type `T`. When the
`unique_ptr` is destroyed, it deletes the object.

```cpp
#include <memory>

{
    std::unique_ptr<Sensor> s = std::make_unique<Sensor>("Thermistor");
    s->read();                 // use it like a pointer: -> and *
    (*s).read();
}   // s is destroyed here -> the Sensor is deleted automatically
```

- **`std::make_unique<T>(args...)`** creates the object with `new` and
  wraps it, in one step. It takes the same arguments as `T`'s
  constructor. Use it instead of writing `new` yourself.
- `->` and `*` work exactly like a raw pointer.
- A `unique_ptr` can be empty (`nullptr`). Test it like a pointer:
  `if (s) { ... }` or `if (s != nullptr) { ... }`.

`unique_ptr` costs nothing extra compared to a raw pointer — it's the
same size, and as fast — so there's no reason not to use it.

### It can't be copied — only moved

"Unique" means unique. If a `unique_ptr` could be copied, two of them
would own the same object and both would delete it (the Module 24 bug
yet again). So copying is **deleted**: `unique_ptr` is a **move-only
type**, exactly like Module 25's `SerialPort`.

```cpp
std::unique_ptr<Sensor> a = std::make_unique<Sensor>("A");
std::unique_ptr<Sensor> b = a;              // ERROR: can't copy a unique_ptr
std::unique_ptr<Sensor> c = std::move(a);   // OK: ownership moves to c; a is now empty
```

### Useful members

| Expression | Meaning |
|---|---|
| `p.get()` | The raw pointer, *without* giving up ownership (for borrowing — see below) |
| `p.reset()` | Delete the object now; `p` becomes empty |
| `p.reset(new T(...))` | Delete the old object, take ownership of a new one |
| `p.release()` | Give up ownership and return the raw pointer — **you** must now delete it. Rarely needed. |
| `if (p)` | Is there an object? |

[`examples/01_unique_ptr_basics.cpp`](examples/01_unique_ptr_basics.cpp)
traces creation, moving, `reset`, and automatic deletion.

## Transferring vs borrowing

Once ownership is visible in the types, function signatures start to
say exactly what they do:

```cpp
// Creates something and gives ownership to the caller.
std::unique_ptr<Sensor> createSensor(std::string name);

// TAKES ownership: the caller hands the sensor over and loses it.
void install(std::unique_ptr<Sensor> sensor);
install(std::move(mySensor));          // must std::move - you're giving it away

// BORROWS: uses the sensor for a while; ownership doesn't change.
void calibrate(Sensor& sensor);        // when a sensor is always required
void printIfPresent(const Sensor* s);  // when "no sensor" (nullptr) is allowed
calibrate(*mySensor);
printIfPresent(mySensor.get());
```

This is the modern rule for raw pointers and references:

> **A raw pointer or reference never owns.** It's a temporary
> *borrow*. Only smart pointers (and other RAII objects) own.

So raw pointers are still fine — as long as they're only *looking* at
something someone else owns, and the owner outlives the borrow. What
you stop doing is writing `new` and `delete` yourself.

Prefer passing a **reference** (`Sensor&` / `const Sensor&`) when the
function just needs the object. Don't pass `const std::unique_ptr<Sensor>&`
— it needlessly ties the function to one particular way of owning the
object.

[`examples/02_transfer_and_borrow.cpp`](examples/02_transfer_and_borrow.cpp)
shows a factory, a function that takes ownership, and functions that
borrow.

## Polymorphic containers — fixing Part 2 for good

Remember Module 12:

```cpp
std::vector<Component*> circuit;
circuit.push_back(new Resistor(220.0));
// ...
for (Component* c : circuit) {
    delete c;      // easy to forget; skipped entirely if an exception happens first
}
```

With `unique_ptr`:

```cpp
std::vector<std::unique_ptr<Component>> circuit;
circuit.push_back(std::make_unique<Resistor>(220.0));
circuit.push_back(std::make_unique<Capacitor>(0.000001));

for (const std::unique_ptr<Component>& c : circuit) {
    c->describe();          // virtual dispatch works exactly as before
}
// No delete loop. When circuit is destroyed, each unique_ptr deletes its object.
```

- `std::make_unique<Resistor>(...)` returns a `unique_ptr<Resistor>`,
  which converts automatically to a `unique_ptr<Component>` — just like
  a `Resistor*` converts to a `Component*`.
- Loop by **reference** (`const std::unique_ptr<Component>&`) — a copy
  isn't allowed. Many people write `const auto& c` here. (`auto` asks
  the compiler to work out the type for you; it's handy with these long
  type names.)
- The **virtual destructor** rule from Module 12 still applies: the
  `unique_ptr<Component>` deletes through a `Component*`, so
  `Component` needs a `virtual` destructor.

[`examples/03_polymorphic_unique_ptr.cpp`](examples/03_polymorphic_unique_ptr.cpp)
is Module 12's circuit, rewritten.

## `std::shared_ptr` — shared ownership

Sometimes an object genuinely has **several owners**, and should live
until the *last* of them is finished with it. For example, a hospital
`Patient` record might be held by a ward's list, a doctor's caseload,
and a pending lab order — and none of them is "the" owner.

A `std::shared_ptr<T>` keeps a **reference count**: how many
`shared_ptr`s currently point at the object. Copying a `shared_ptr`
increases the count; destroying one decreases it; when the count
reaches **zero**, the object is deleted.

```cpp
std::shared_ptr<Patient> p = std::make_shared<Patient>("Esi Badu");
std::cout << p.use_count();   // 1

{
    std::shared_ptr<Patient> onCaseload = p;   // copying is allowed: count = 2
    std::shared_ptr<Patient> onLabOrder = p;   // count = 3
}                                              // two copies destroyed: count = 1

p.reset();                                     // count = 0 -> Patient deleted
```

- Create them with **`std::make_shared<T>(args...)`**.
- `use_count()` reports the current count (useful for learning and
  debugging; rarely needed in real logic).

`shared_ptr` is very convenient, but it has costs:

- It's bigger and slower than `unique_ptr`: the count must be stored
  and updated (safely, even from multiple threads).
- More importantly, it makes ownership **vague again**. When everything
  is shared, it's hard to know when anything is actually destroyed.

> **Default to `unique_ptr`.** Use `shared_ptr` only when there truly
> is no single owner. It's easy to convert a `unique_ptr` into a
> `shared_ptr` later (`std::shared_ptr<T> s = std::move(u);`); going
> the other way isn't possible.

[`examples/04_shared_ptr.cpp`](examples/04_shared_ptr.cpp) traces the
reference count as owners come and go.

## `std::weak_ptr` — observing without owning

Shared ownership has one trap: **cycles**.

```cpp
class Parent { std::shared_ptr<Child> child; };
class Child  { std::shared_ptr<Parent> parent; };
```

If a parent owns its child and the child owns its parent, then even
after everything else lets go, each one keeps the other's count at 1.
Neither count ever reaches zero, so **neither is ever deleted** — a
leak, created without a single raw `new`.

The fix is **`std::weak_ptr`**: a pointer that *refers to* an object
managed by `shared_ptr`s, but **doesn't own it** and doesn't increase
its count.

```cpp
class Child {
    std::weak_ptr<Parent> parent;   // observes, doesn't own - breaks the cycle
};
```

Because a `weak_ptr` doesn't keep its object alive, the object might
already be gone when you want to use it. So you can't use a `weak_ptr`
directly — you must **`lock()`** it, which gives you a `shared_ptr`
that is either valid or empty:

```cpp
if (std::shared_ptr<Parent> p = parent.lock()) {
    p->doSomething();       // safe: p keeps the Parent alive while we use it
} else {
    // the Parent has already been destroyed
}
```

`expired()` tells you whether the object is gone without locking it.

[`examples/05_weak_ptr_cycle.cpp`](examples/05_weak_ptr_cycle.cpp)
creates a cycle that leaks (watch for the missing destructor messages)
and then fixes it with `weak_ptr`.

## Choosing the right tool

| Situation | Use |
|---|---|
| One clear owner (the common case) | `std::unique_ptr<T>` |
| A class member that owns a heap object | `std::unique_ptr<T>` member — and the class then follows the Rule of Zero (it becomes move-only automatically) |
| A polymorphic collection | `std::vector<std::unique_ptr<Base>>` |
| A function that *creates* an object for the caller | return `std::unique_ptr<T>` |
| A function that *uses* an object | take `T&` / `const T&` (or `T*` / `const T*` if it may be absent) |
| A function that *takes ownership* | take `std::unique_ptr<T>` by value |
| Several owners, none more important than the others | `std::shared_ptr<T>` |
| Refer to a `shared_ptr`-managed object without keeping it alive (and break cycles) | `std::weak_ptr<T>` |
| A non-owning pointer that might be null | raw `T*` (a borrow) |
| An object that doesn't need to be on the heap at all | **no pointer** — just a normal variable or member |

That last row matters. The best pointer is often no pointer: if an
object can simply be a member or a local variable, make it one.

## Common beginner mistakes

- Writing `std::unique_ptr<Sensor> p(new Sensor(...));` instead of
  `std::make_unique<Sensor>(...)`. It works, but `make_unique` is
  shorter, safer, and means you never type `new`.
- Trying to copy a `unique_ptr` (passing it by value without
  `std::move`, or looping over a vector of them by value). The fix is
  `std::move` to transfer, or a reference to borrow.
- Using a `unique_ptr` after moving from it — it's now empty
  (`nullptr`).
- Calling `delete p.get()` — the `unique_ptr` will delete it again.
- Creating two separate smart pointers from the same raw pointer — two
  owners, double delete.
- Making everything a `shared_ptr` "to be safe". It hides ownership and
  invites cycles. Default to `unique_ptr`.
- Two objects holding `shared_ptr`s to each other (a cycle) — make one
  direction a `weak_ptr`.
- Forgetting the `virtual` destructor on a base class used through
  `unique_ptr<Base>`.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md), continuing your
   track.
4. Commit:

   ```bash
   git add 26-smart-pointers
   git commit -m "Complete Module 26: smart pointers and ownership"
   git push
   ```

Next: **[Module 27 — Composition, Aggregation & Association](../27-composition-aggregation/README.md)**.
