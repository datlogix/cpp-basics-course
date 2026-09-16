# Module 12 — Polymorphism & Virtual Functions

Module 11 ended on a gap: overriding a method works fine when you call
it through a variable of the derived type, but breaks down the moment
you access the same object through a **base class pointer or
reference**. This module closes that gap with one keyword: `virtual`.
It's the payoff that makes inheritance genuinely powerful, not just a
way to avoid retyping code.

## The problem, demonstrated

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
    void describe() {
        std::cout << name << ": " << value << " ohms" << std::endl;
    }
};

void printIt(Component c) {
    c.describe();
}

int main() {
    Resistor r(220.0);
    r.describe();       // "Resistor: 220 ohms" - correct, Resistor's version
    printIt(r);          // "Resistor: 220" - WRONG unit! Component's version ran
    return 0;
}
```

Passing `r` into `printIt(Component c)` **copies only the `Component`
part** of `r` — this is called **object slicing**. The function has no
idea it was ever a `Resistor`. The same problem happens with a
`Component*` pointer to a `Resistor` object: without `virtual`, the
pointer's *declared* type decides which `describe()` runs, not the
object's *actual* type.

This matters enormously in practice, because the entire point of
inheritance is usually to build a collection of **different** derived
objects and treat them uniformly:

```cpp
std::vector<Component*> circuit;
circuit.push_back(new Resistor(220.0));
circuit.push_back(new Capacitor(0.000001));
// Without virtual, calling describe() on each Component* runs
// Component's version for ALL of them - the whole point of the
// collection is defeated.
```

## The fix: `virtual`

```cpp
class Component {
protected:
    std::string name;
    double value;
public:
    Component(std::string n, double v) : name(n), value(v) {}
    virtual void describe() {              // <-- virtual
        std::cout << name << ": " << value << std::endl;
    }
    virtual ~Component() {}                // <-- see "virtual destructors" below
};

class Resistor : public Component {
public:
    Resistor(double ohms) : Component("Resistor", ohms) {}
    void describe() override {             // <-- override (see below)
        std::cout << name << ": " << value << " ohms" << std::endl;
    }
};
```

`virtual` tells the compiler: "don't decide which version of this
function to call based on the pointer/reference's declared type — look
at the object's *actual* type, at runtime, every time." This is called
**dynamic dispatch**, and it's the technical name for what people mean
by "polymorphism" in C++.

```cpp
void printIt(Component& c) {   // note: reference, not by-value copy
    c.describe();               // now correctly calls the ACTUAL type's version
}

int main() {
    Resistor r(220.0);
    printIt(r);   // "Resistor: 220 ohms" - correct now
    return 0;
}
```

Two changes were required together: `virtual` on the base class method,
**and** passing/storing by pointer or reference instead of by value
(pass-by-value still slices, virtual or not — there's no object left to
dispatch on after the copy already happened).

## `override` — a safety net, not a requirement

```cpp
void describe() override { ... }
```

`override` isn't required for polymorphism to work, but you should use
it on every method you intend as an override. It tells the compiler
"this is supposed to override a virtual base method — if it doesn't
actually match one (a typo in the name, a mismatched parameter type),
fail to compile instead of silently creating an unrelated new method."
This catches a very easy, very silent mistake.

## The payoff: a polymorphic collection

```cpp
std::vector<Component*> circuit;
circuit.push_back(new Resistor(220.0));
circuit.push_back(new Capacitor(0.000001));
circuit.push_back(new Inductor(0.05));

for (Component* c : circuit) {
    c->describe();   // -> correctly calls EACH object's own version
}
```

`->` is the arrow operator: `c->describe()` is shorthand for
`(*c).describe()` — dereference the pointer, then call the method. This
loop is the entire reason polymorphism exists: one piece of code,
written once, correctly handles every current and future derived type
without ever checking "what kind of Component is this?" by hand.

## Virtual destructors — a rule to just follow

```cpp
virtual ~Component() {}
```

If a base class will ever be deleted through a base class pointer
(`Component* c = new Resistor(...); delete c;`), its destructor **must**
be `virtual`, or only the base class's part of the object gets cleaned
up — a real, silent memory/resource leak. The rule of thumb: **any class
designed to be a polymorphic base class should have a virtual
destructor**, even if it does nothing itself.

## Abstract base classes and pure virtual functions (a brief preview)

Sometimes a base class shouldn't be instantiable on its own — `Component`
by itself is too generic to ever create directly; it only makes sense as
`Resistor`, `Capacitor`, etc. Marking a virtual function **pure**
(`= 0`) enforces this:

```cpp
virtual void describe() = 0;   // no body - EVERY derived class MUST provide one
```

A class with any pure virtual function becomes an **abstract class** —
you can no longer write `Component c(...)` directly, only derive from
it. This course doesn't require you to use this, but recognizing
`= 0` in code you read elsewhere is worth having now.

## Common beginner mistakes

- Forgetting `virtual` on the base method, then being confused why the
  base version keeps running through a base pointer/reference.
- Passing/storing polymorphic objects **by value** instead of by
  pointer or reference (object slicing) — `virtual` cannot fix this;
  the object has already been copied down to its base part.
- Forgetting a virtual destructor on a polymorphic base class.
- Assuming `override` is what makes polymorphism work — it's a
  compile-time safety check; `virtual` on the base is what actually
  enables dynamic dispatch.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — pick the Generic,
   EE, or Biomedical track.
4. Commit:

   ```bash
   git add 12-polymorphism
   git commit -m "Complete Module 12: polymorphism and virtual functions"
   git push
   ```

Next: **[Module 13 — Operator Overloading](../13-operator-overloading/README.md)**.
