# Module 30 — Operator Overloading II & Friends

Module 13 taught you to overload `+`, `==`, and `<<` so that your own
types read naturally: `a + b`, `a == b`, `std::cout << a`. You also met
`friend` there, as part of the `<<` recipe. This module completes the
picture so you can build **value types** — classes like `Money`,
`Vector2D`, `Fraction` or `Phasor` — that behave as naturally as
`int` and `double`:

- **`friend`** functions and classes, properly — and when *not* to use
  them
- **member vs non-member** operators, and why symmetry matters
- **compound assignment** (`+=`, `-=`, ...) and writing `+` in terms of
  `+=`
- **increment and decrement** (`++`/`--`), prefix and postfix
- the **subscript** operator `[]`, with `const` and non-`const`
  versions
- the **function call** operator `()` — **function objects**
  (functors), and how they work with STL algorithms
- **`>>`** for input
- **conversion operators**, and `explicit operator bool`
- **comparisons** with C++20's three-way comparison operator **`<=>`**

## `friend` — granting access deliberately

A class's `private` members are only accessible to its own member
functions. A **`friend`** declaration inside a class grants access to a
specific outside function or class:

```cpp
class Money {
private:
    long pesewas;   // stored as whole pesewas (1 cedi = 100 pesewas) to avoid rounding errors
public:
    explicit Money(long p) : pesewas(p) {}

    friend std::ostream& operator<<(std::ostream& os, const Money& m);   // a friend FUNCTION
    friend class Auditor;                                               // a friend CLASS
};
```

- A friend **function** is *not* a member — it has no `this`, and isn't
  called with `.` — but it can read the class's private members.
- A friend **class**: every member function of `Auditor` can access
  `Money`'s private members.
- Friendship is **granted, not taken**: only the class itself can
  declare who its friends are. It's **not inherited** and **not
  mutual** (`Auditor` being `Money`'s friend doesn't make `Money`
  `Auditor`'s friend).

Isn't this a hole in encapsulation? Only if overused. A friend that's
declared *inside the class*, right next to the members it uses, is
really part of the class's interface — it just can't be written as a
member for syntactic reasons (like `<<`, whose left side is a stream).
Use `friend` for:

- operators that need private access but can't be members (`<<`, `>>`,
  symmetric binary operators — see below);
- a small, tightly coupled helper class (like Module 27's doctor/patient
  example, where `Doctor` kept both sides of an association
  consistent).

Don't use it as a shortcut to avoid designing a proper public
interface. If you're tempted to make an unrelated class a friend "so it
can get at the data", reconsider.

[`examples/01_friend.cpp`](examples/01_friend.cpp) shows a friend
function and a friend class.

## Member or non-member? Symmetry

You can write a binary operator as a **member** (the left operand is
`*this`) or as a **non-member** (both operands are parameters):

```cpp
class Vector2D {
public:
    double x, y;
    Vector2D operator*(double k) const { return {x * k, y * k}; }   // member: v * 2.0
};

Vector2D operator*(double k, const Vector2D& v) { return v * k; }    // non-member: 2.0 * v
```

A member operator only works when **your type is on the left**. `v * 2.0`
calls `v.operator*(2.0)`; but `2.0 * v` would need
`2.0.operator*(v)` — and you can't add methods to `double`. So for
operations that should work **either way round**, provide a
non-member.

Common guidance:

| Operator | Usually written as |
|---|---|
| `=`, `[]`, `()`, `->` | **must** be members |
| `+=`, `-=`, `*=`, ... (they modify the left operand) | members |
| `++`, `--` | members |
| `+`, `-`, `*`, `/` | non-members (symmetry), often written using `+=` etc. |
| `==`, `<`, `<=>` | non-members, or members (C++20 makes members symmetric automatically) |
| `<<`, `>>` with streams | **must** be non-members (often friends) |

## Compound assignment, and `+` in terms of `+=`

Compound assignment **modifies** the left operand and returns it by
reference (so it can be chained, like built-in types):

```cpp
class Money {
    long pesewas;
public:
    Money& operator+=(const Money& other) {
        pesewas += other.pesewas;
        return *this;
    }
    Money& operator-=(const Money& other) {
        pesewas -= other.pesewas;
        return *this;
    }
};
```

Then `+` can reuse `+=` — so the actual arithmetic lives in **one
place**:

```cpp
Money operator+(Money left, const Money& right) {   // left is a COPY (by value)
    left += right;                                   // modify the copy
    return left;                                     // return it
}
```

This pattern — `+=` as a member doing the real work, `+` as a non-member
built on it — is the standard way to write arithmetic operators.

[`examples/02_compound_and_binary.cpp`](examples/02_compound_and_binary.cpp)
builds a `Vector2D` with `+=`, `+`, `-`, and symmetric `*`.

## Increment and decrement: prefix vs postfix

`++x` (**prefix**) increments, then gives you the **new** value.
`x++` (**postfix**) gives you the **old** value, and increments. Your
type can support both. C++ tells them apart with a dummy `int`
parameter on the postfix version:

```cpp
class Counter {
    int value = 0;
public:
    Counter& operator++() {          // PREFIX: ++c
        ++value;
        return *this;                // return the object itself (the new value)
    }

    Counter operator++(int) {        // POSTFIX: c++  (the int is never used - it's just a marker)
        Counter old = *this;         // remember the old value
        ++value;                     // increment
        return old;                  // return the OLD value, by value
    }
};
```

Notice the postfix version must make a **copy** of the old value. That's
why many C++ programmers prefer `++i` to `i++` when they don't need the
old value — for class types, it can be cheaper.

[`examples/03_increment.cpp`](examples/03_increment.cpp) builds a
`ClassPeriod` type that steps through the school day with `++`/`--`.

## The subscript operator `[]`

`[]` lets your class be indexed like an array. You almost always need
**two** versions:

```cpp
class Gradebook {
    std::vector<double> scores;
public:
    double& operator[](int i) { return scores[i]; }               // non-const: allows g[2] = 75;
    const double& operator[](int i) const { return scores[i]; }   // const: for const Gradebooks
};
```

- The non-`const` version returns a **reference**, so `g[2] = 75;`
  writes into the object.
- The `const` version is chosen for `const` objects (and `const&`
  parameters, Module 21) and returns a `const` reference, so reading
  works but writing doesn't compile.

`[]` doesn't have to take an integer: a class could support
`registry["Ama"]`. And it's a good place to add **bounds checking**,
which plain arrays don't have (throwing an exception — Module 15 and
Module 31).

[`examples/04_subscript.cpp`](examples/04_subscript.cpp) shows both
versions, with a bounds check.

## The function call operator `()` — function objects

If a class overloads `operator()`, its objects can be **called like
functions**. Such objects are called **function objects**, or
**functors**:

```cpp
class IsAbove {
    double threshold;
public:
    explicit IsAbove(double t) : threshold(t) {}
    bool operator()(double value) const { return value > threshold; }
};

IsAbove fever(38.0);
fever(39.2);   // true - looks like a function call, but it's an object
```

Why not just write a function? Because a functor **carries data** —
here, its threshold — chosen when it's created. That's exactly what
STL algorithms (Module 17) need:

```cpp
int feverCount = std::count_if(temps.begin(), temps.end(), IsAbove(38.0));
```

That should look familiar: it's what a **lambda** does. In fact, a
lambda like `[threshold](double v) { return v > threshold; }` is the
compiler writing a functor class for you, with the captured variables
as members. Use lambdas for short, one-off predicates; write a named
functor class when the behaviour is reused, has a meaningful name, or
needs several members or methods.

[`examples/05_functor.cpp`](examples/05_functor.cpp) uses functors with
`count_if`, `sort` and `transform`, next to equivalent lambdas.

## `>>` for input

`>>` mirrors Module 13's `<<`: a non-member, usually a friend, taking
the stream by reference and returning it:

```cpp
std::istream& operator>>(std::istream& in, Money& m) {
    double cedis;
    if (in >> cedis) {                              // only change m if reading worked
        m.pesewas = std::lround(cedis * 100);
    }
    return in;
}
```

- The object parameter is a **non-`const`** reference — you're filling
  it in.
- Return the stream so `std::cin >> a >> b;` chains.
- If the input is invalid, the stream goes into a failed state (exactly
  as with `int` in Module 3/14) and the object should be left
  unchanged. Callers check it the usual way: `if (std::cin >> m)`.

Because it works with **any** input stream, the same `>>` reads from
`std::cin`, from a file (`std::ifstream`), or from a string
(`std::istringstream` — handy for testing).

[`examples/06_stream_input.cpp`](examples/06_stream_input.cpp) reads
values from a string stream and from the keyboard.

## Conversion operators

A **conversion operator** lets an object be converted to another type:

```cpp
class Percentage {
    double value;
public:
    explicit operator double() const { return value / 100.0; }   // Percentage -> double
};

Percentage p(45);
double fraction = static_cast<double>(p);   // 0.45
```

Remember Module 21's lesson about single-argument constructors: silent
conversions cause surprises. The same is true here, so **mark
conversion operators `explicit`**, which means the conversion only
happens when asked for with `static_cast` (or in a condition, below).

The most common one is **`explicit operator bool`**, which lets an
object be tested in an `if`, just like a stream or a smart pointer:

```cpp
class SensorReading {
    double value;
    bool ok;
public:
    explicit operator bool() const { return ok; }
};

if (reading) { ... }          // OK: conditions are allowed to use an explicit bool conversion
int x = reading + 1;          // ERROR - which is exactly what we want
```

[`examples/07_conversion_operators.cpp`](examples/07_conversion_operators.cpp)
shows both.

## Comparisons, and the spaceship operator `<=>` (C++20)

To sort your objects (`std::sort`, Module 17) or keep them in a
`std::set` or as `std::map` keys (Module 16), they need `<`. Writing all
six comparisons by hand (`==`, `!=`, `<`, `<=`, `>`, `>=`) is tedious
and easy to get inconsistent.

C++20 adds the **three-way comparison operator**, `<=>` (nicknamed the
"spaceship" because of its shape). `a <=> b` answers "less, equal, or
greater?" in one go. Better still, you can ask the compiler to write it:

```cpp
#include <compare>

class Version {
    int major, minor, patch;
public:
    auto operator<=>(const Version&) const = default;   // compares major, then minor, then patch
    bool operator==(const Version&) const = default;
};
```

With those two defaulted lines, **all six** comparison operators work,
comparing the members **in declaration order** — exactly the "compare
by first field, then by the next" logic you'd otherwise write by hand.

When the default order isn't what you want (e.g. compare `Money` by its
pesewas only, or sort students by average), write `<=>` yourself:

```cpp
std::strong_ordering operator<=>(const Money& other) const {
    return pesewas <=> other.pesewas;
}
bool operator==(const Money& other) const { return pesewas == other.pesewas; }
```

The return type says what kind of ordering it is (both types come from
`<compare>`):

- `std::strong_ordering` — for whole numbers, strings, and most simple
  types: any two values are either less, equal, or greater.
- `std::partial_ordering` — for `double`s, where some values can't be
  compared at all (a "not-a-number" result, such as `0.0 / 0.0`, is
  neither less, equal nor greater than anything). Comparing two
  `double`s with `<=>` gives a `partial_ordering`.

> **This needs C++20.** Compile examples that use `<=>` with
> `-std=c++20` instead of `-std=c++17` (GCC 10+, Clang 10+, recent
> MSVC). If your compiler is older, define `==` and `<` yourself as in
> Module 13 — `std::sort` and `std::map` only need `<`.

[`examples/08_spaceship.cpp`](examples/08_spaceship.cpp) sorts and
compares values with defaulted and hand-written `<=>`.

## Choosing operators well — a reminder

Module 13's rule still applies, and matters more now that you can
overload almost anything: **only overload an operator when its meaning
for your type is obvious to a reader**. `money1 + money2` is obvious.
`student + course` is not — write `student.enrol(course)`. Overloading
`&&`, `||`, or `,` is almost never a good idea (they lose their
special short-circuit/ordering behaviour when overloaded).

## Common beginner mistakes

- Writing a symmetric operator (`*` with a `double`) only as a member,
  so `2.0 * v` doesn't compile.
- Returning a copy from `+=` (should return `*this` by reference), or a
  reference from `+` (should return a new value — never a reference to
  a local variable).
- Mixing up prefix and postfix: prefix returns `*this` by reference;
  postfix takes a dummy `int` and returns the old value by value.
- Providing only a non-`const` `operator[]`, so indexing a
  `const` object doesn't compile.
- `operator>>` taking the object by `const&` (it must modify it), or
  changing the object even when reading failed.
- Non-`explicit` conversion operators causing silent, surprising
  conversions.
- Using `<=>` without `-std=c++20`, or forgetting `#include <compare>`.
- Making unrelated classes `friend`s to dodge proper interface design.

## Try it yourself

1. Work through [`examples/`](examples/). Use `-std=c++20` for
   `08_spaceship.cpp`.
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md), continuing your
   track.
4. Commit:

   ```bash
   git add 30-operator-overloading-ii
   git commit -m "Complete Module 30: operator overloading II and friends"
   git push
   ```

Next: **[Module 31 — Exceptions in Class Design](../31-exceptions-in-class-design/README.md)**.
