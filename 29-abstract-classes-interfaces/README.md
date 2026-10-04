# Module 29 — Abstract Classes, Interfaces & Advanced Polymorphism

Module 12 introduced polymorphism and gave a "brief preview" of
abstract classes: a function marked `= 0` makes a class impossible to
create directly. Since then you've used `= 0` in several Part 3
starters. This module finishes the story:

- **pure virtual functions** and **abstract classes**, properly
- abstract classes that provide **some** shared behaviour (the
  "template method" idea)
- **interfaces** — classes that are *only* a contract
- **programming to an interface**
- what's really happening underneath: the **vtable**
- **static vs dynamic binding** — when `virtual` does and doesn't apply
- **`dynamic_cast`** and **`typeid`** (RTTI) — and why needing them is
  often a design smell
- **covariant return types** and the `clone()` idiom (polymorphic
  copying)
- the trap of calling virtual functions from **constructors and
  destructors**

## Pure virtual functions and abstract classes

A **pure virtual function** is a virtual function with `= 0` instead
of a body:

```cpp
class Shape {
public:
    virtual ~Shape() {}
    virtual double area() const = 0;        // pure virtual
    virtual std::string name() const = 0;   // pure virtual
};
```

It means: *"every shape has an area, but there is no sensible general
formula — each kind of shape must provide its own."*

A class with at least one pure virtual function is an **abstract
class**:

- You **cannot create an object** of an abstract class:
  `Shape s;` is a compile error.
- You **can** have pointers and references to it — that's the whole
  point: `std::unique_ptr<Shape>`, `const Shape&`.
- A derived class that overrides **every** pure virtual function is
  **concrete**, and can be created. A derived class that leaves even
  one unimplemented is **still abstract**.

```cpp
class Circle : public Shape {
    double r;
public:
    explicit Circle(double radius) : r(radius) {}
    double area() const override { return 3.14159 * r * r; }
    std::string name() const override { return "Circle"; }
};

Shape s;                 // ERROR: Shape is abstract
Circle c(2.0);           // OK: Circle is concrete
const Shape& ref = c;    // OK: a reference to the abstract type
```

Why is this better than Module 12's "default" virtual function that
returned `0`? Because a default of `0` is a **lie** that compiles. If
someone adds a `Triangle` and forgets `area()`, the program silently
reports an area of zero. With `= 0`, forgetting is a **compile error**
— the moment anyone tries to create a `Triangle`.

## Abstract classes can still share code

"Abstract" doesn't mean "empty". An abstract class can have data
members, constructors, and fully implemented methods alongside its pure
virtual ones. A powerful pattern is a **non-virtual public method that
does the common steps, and calls pure virtual methods for the parts
that differ**:

```cpp
class Sensor {
protected:
    std::string name;
public:
    explicit Sensor(std::string n) : name(n) {}
    virtual ~Sensor() {}

    // The SAME procedure for every sensor...
    void report() const {
        double value = read();                    // ...with the varying steps
        std::cout << name << ": " << value << " " << unit();
        if (!inSafeRange(value)) std::cout << "  ** OUT OF RANGE **";
        std::cout << std::endl;
    }

protected:
    virtual double read() const = 0;             // ...supplied by each sensor
    virtual std::string unit() const = 0;
    virtual bool inSafeRange(double v) const = 0;
};
```

Every sensor reports in exactly the same format, and a new sensor only
has to fill in three small, focused functions. This is called the
**Template Method** pattern (nothing to do with C++ templates — Module
34 covers it with other patterns). Notice the pure virtual functions
are `protected`: they're steps of `report()`, not something outsiders
should call directly.

[`examples/01_abstract_class.cpp`](examples/01_abstract_class.cpp)
builds this sensor family.

## Interfaces

An **interface** is an abstract class taken to the extreme: **only**
pure virtual functions (plus a virtual destructor), and **no data**.
It describes a *capability* — what something can do — and nothing
about how.

```cpp
class Printable {
public:
    virtual ~Printable() = default;
    virtual void print() const = 0;
};

class Saveable {
public:
    virtual ~Saveable() = default;
    virtual std::string toCsv() const = 0;
};
```

C++ has no `interface` keyword (unlike Java or C#); an interface is
just this style of class. Some teams name them with a leading `I`
(`IPrintable`) to make the role obvious; this course uses plain
capability names like `Printable`.

(`= default` on the destructor asks for the compiler's normal version
— Module 24 — while still making it `virtual`. It's the usual way to
write an interface's destructor.)

A class can implement **several** interfaces — the safe kind of
multiple inheritance from Module 28, because interfaces have no data
to duplicate:

```cpp
class StudentRecord : public Printable, public Saveable {
public:
    void print() const override;
    std::string toCsv() const override;
};
```

## Programming to an interface

The real power of interfaces is in the code that **uses** them:

```cpp
void saveAll(const std::vector<const Saveable*>& items, std::ofstream& file) {
    for (const Saveable* item : items) {
        file << item->toCsv() << "\n";
    }
}
```

`saveAll` doesn't know or care whether it's saving students, sensor
readings, or invoices. It depends only on the *capability*. You can add
a completely new kind of saveable thing next year, and `saveAll` works
with it **without being changed or even recompiled**. This idea —
"depend on abstractions, not concrete classes" — is the heart of good
OO design, and Module 33 gives it a formal name (the Dependency
Inversion Principle).

[`examples/02_interfaces.cpp`](examples/02_interfaces.cpp) has classes
that implement one or both interfaces, and functions that work with
each.

## Under the hood: the vtable

How does `shape->area()` know, at runtime, which `area()` to run? Most
compilers use the same simple mechanism:

- For each class with virtual functions, the compiler builds one
  **virtual table** (**vtable**): an array of addresses of that class's
  versions of each virtual function.
- Each **object** of such a class contains a hidden pointer (the
  **vptr**) to its class's vtable, set by the constructor.
- A virtual call `shape->area()` becomes: follow the object's vptr to
  its vtable, look up the `area` slot, call whatever function is there.

```
 Circle object               Circle's vtable
 +------------+              +---------------------------+
 | vptr  -----+------------> | ~Circle                   |
 | r = 2.0    |              | Circle::area   (slot 1)   |
 +------------+              | Circle::name   (slot 2)   |
                             +---------------------------+

 Square object               Square's vtable
 +------------+              +---------------------------+
 | vptr  -----+------------> | ~Square                   |
 | side = 3   |              | Square::area   (slot 1)   |
 +------------+              | Square::name   (slot 2)   |
                             +---------------------------+
```

Consequences worth knowing:

- Each polymorphic object is slightly bigger (one hidden pointer).
- A virtual call costs one extra memory lookup — tiny, and almost never
  worth worrying about.
- An abstract class's vtable has an empty slot for each pure virtual
  function — which is exactly why you can't create one.

[`examples/03_static_vs_dynamic_binding.cpp`](examples/03_static_vs_dynamic_binding.cpp)
shows the hidden pointer's effect with `sizeof`.

## Static vs dynamic binding

**Binding** means deciding which function a call refers to.

- **Static binding** (at compile time) is decided by the **declared
  type** of the expression. It's used for non-virtual functions, for
  calls on objects (not pointers/references), and for explicitly
  qualified calls like `Shape::describe()`.
- **Dynamic binding** (at runtime, through the vtable) is decided by
  the **actual type** of the object. It's used only for **virtual**
  functions called through a **pointer or reference**.

```cpp
Circle c(2.0);
Shape& s = c;

s.area();          // dynamic: virtual via reference -> Circle::area
c.area();          // static: called on an object of known type -> Circle::area
s.describe();      // static if describe() is NOT virtual -> Shape::describe, even for a Circle!
```

The third line is the classic Module 12 surprise, now with a name: a
**non-virtual** function is statically bound, so it never dispatches to
the derived version.

## `dynamic_cast` — asking "are you really a ...?"

Sometimes you hold a base pointer and genuinely need to know whether
the object is a particular derived type. **`dynamic_cast`** checks at
runtime:

```cpp
for (const auto& s : shapes) {
    if (const Circle* c = dynamic_cast<const Circle*>(s.get())) {
        std::cout << "a circle of radius " << c->getRadius() << std::endl;
    }
}
```

- With **pointers**: returns the derived pointer if the object really
  is that type (or derived from it), otherwise `nullptr`.
- With **references**: returns the derived reference, or **throws**
  `std::bad_cast` if it isn't (because there's no "null reference").
- It only works on **polymorphic** classes (ones with at least one
  virtual function), because it uses the vtable's type information.

**`typeid`** (from `<typeinfo>`) gives you an object's actual type:
`typeid(*s) == typeid(Circle)`. `typeid(x).name()` returns a
compiler-specific name, useful for debugging but not for display.

These two features are called **RTTI** — **R**un-**T**ime **T**ype
**I**nformation.

### Why needing them is often a smell

Look at this:

```cpp
double totalArea(const std::vector<std::unique_ptr<Shape>>& shapes) {
    double total = 0;
    for (const auto& s : shapes) {
        if (auto c = dynamic_cast<const Circle*>(s.get()))      total += 3.14159 * c->r * c->r;
        else if (auto q = dynamic_cast<const Square*>(s.get())) total += q->side * q->side;
        // ...and every new shape needs a new branch here
    }
    return total;
}
```

This is the "check what kind of thing it is" code that polymorphism
exists to *remove* (Module 12). Every new shape means finding and
editing every chain like this. The fix is a virtual function:
`total += s->area();`.

> **Guideline:** if you find yourself writing `dynamic_cast` chains or
> `typeid` comparisons to choose behaviour, you probably want a
> virtual function instead. Use `dynamic_cast` for the rare cases where
> a specific capability genuinely only exists on some objects — and
> even then, consider whether an interface (`dynamic_cast<const
> Saveable*>`) is the real question.

[`examples/04_dynamic_cast_typeid.cpp`](examples/04_dynamic_cast_typeid.cpp)
shows both tools — and the virtual-function version that replaces them.

## Polymorphic copying: `clone()` and covariant return types

You have a `std::vector<std::unique_ptr<Shape>>`, and you want a
**copy** of one shape — but you don't know which kind it is. You can't
write `Shape copy = *s;` (that would slice, and `Shape` is abstract
anyway). The standard solution is a **virtual `clone()`** method:

```cpp
class Shape {
public:
    virtual ~Shape() = default;
    virtual std::unique_ptr<Shape> clone() const = 0;
};

class Circle : public Shape {
public:
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);   // copy-construct a Circle
    }
};
```

Each class knows how to copy itself, so `s->clone()` copies a circle
as a circle and a square as a square.

**Covariant return types:** when a virtual function returns a *raw*
pointer or reference, an override is allowed to return a pointer or
reference to a **more derived** type:

```cpp
class Shape  { public: virtual Shape*  cloneRaw() const = 0; };
class Circle : public Shape { public: Circle* cloneRaw() const override; };   // allowed
```

That's handy when the caller knows it has a `Circle` and wants a
`Circle*` back without a cast. It doesn't work with `std::unique_ptr`
return types (they aren't related by inheritance), which is why the
`unique_ptr` version above returns `std::unique_ptr<Shape>`.

[`examples/05_clone_covariant.cpp`](examples/05_clone_covariant.cpp)
deep-copies a whole polymorphic collection with `clone()`.

## The constructor/destructor trap

```cpp
class Sensor {
public:
    Sensor() { std::cout << "Created a " << kind() << std::endl; }   // !!
    virtual std::string kind() const { return "generic sensor"; }
};

class Thermistor : public Sensor {
public:
    std::string kind() const override { return "thermistor"; }
};

Thermistor t;   // prints "Created a generic sensor"
```

While the `Sensor` part of a `Thermistor` is being constructed, the
`Thermistor` part **doesn't exist yet** (Module 23's construction
order). So during the base constructor, the object behaves as a
`Sensor`: virtual calls go to `Sensor`'s versions. If `kind()` were
pure virtual, the program would crash. The same applies, in reverse,
during destructors — the derived part has already been destroyed.

> **Rule:** never rely on virtual dispatch inside a constructor or
> destructor. If derived-specific setup is needed, do it in the derived
> constructor, or have a separate `initialise()` step called after
> construction.

[`examples/06_virtual_in_constructor.cpp`](examples/06_virtual_in_constructor.cpp)
traces this.

## Common beginner mistakes

- Trying to create an object of an abstract class (`Shape s;`) — use a
  concrete derived class, or a pointer/reference.
- Forgetting to override one pure virtual function, then getting a
  confusing "cannot declare variable to be of abstract type" error on
  the *derived* class. The error message lists which function is
  missing — read it.
- Giving a base class a "do-nothing" virtual function where a pure
  virtual would make forgetting impossible.
- Forgetting the virtual destructor on an interface.
- Using `dynamic_cast`/`typeid` chains instead of virtual functions.
- Using `dynamic_cast` on a class with no virtual functions (it won't
  compile).
- Copying a polymorphic object through a base type (slicing) instead
  of using `clone()`.
- Calling virtual functions from constructors or destructors and
  expecting the derived version.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md), continuing your
   track.
4. Commit:

   ```bash
   git add 29-abstract-classes-interfaces
   git commit -m "Complete Module 29: abstract classes, interfaces and advanced polymorphism"
   git push
   ```

Next: **[Module 30 — Operator Overloading II & Friends](../30-operator-overloading-ii/README.md)**.
