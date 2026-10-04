# Module 32 — Templates Meet OOP

Module 18 introduced templates: write a function or class once with a
type parameter `T`, and the compiler generates a real version for each
type you use — the same mechanism behind `std::vector<T>` and
`std::map<K, V>`. You built a `Statistics<T>` class with it.

Since then, you've learned a great deal about classes. This module
brings the two together, and covers what you need to write templates
that are part of a real object-oriented design:

- defining a class template's member functions **outside** the class —
  and why template code lives in **headers**
- **member function templates** (a template method inside a class)
- **non-type template parameters** (`template <typename T, int N>`)
- **template specialisation** — a custom version for one particular
  type
- **templates and inheritance** together
- **static polymorphism** (templates) vs **dynamic polymorphism**
  (`virtual`) — and when to choose each
- a first look at the **CRTP** idiom
- **C++20 concepts**: stating what a template needs from its type,
  with clear error messages

## Recap

```cpp
template <typename T>
class Statistics {
private:
    std::vector<T> values;
public:
    void add(T v) { values.push_back(v); }
    double mean() const;
};

Statistics<double> temps;
Statistics<int> scores;
```

Remember the key idea from Module 18: a template is a **recipe**, not
code. `Statistics<double>` and `Statistics<int>` are two completely
separate classes that the compiler writes for you, on demand, from the
recipe.

## Member functions outside a class template — and why templates live in headers

Module 21 showed defining member functions outside the class with
`ClassName::`. For a class template, every outside definition must
repeat the template header, and the class name includes its parameter:

```cpp
template <typename T>
class Statistics {
    std::vector<T> values;
public:
    void add(T v);
    double mean() const;
};

template <typename T>                       // repeat the template header...
void Statistics<T>::add(T v) {              // ...and write Statistics<T>::
    values.push_back(v);
}

template <typename T>
double Statistics<T>::mean() const {
    if (values.empty()) return 0;
    double total = 0;
    for (const T& v : values) total += v;
    return total / values.size();
}
```

**Where does this code go?** In Module 22, method definitions went in
a `.cpp` file, compiled separately. That doesn't work for templates.
When `main.cpp` uses `Statistics<double>`, the compiler must *generate*
`Statistics<double>::mean` right then — so it needs the **recipe**
(the full definition), not just a declaration. If the definition is
hidden away in `statistics.cpp`, nobody ever generates the `double`
version, and you get an `undefined reference` linker error.

> **Rule:** put a template's member function definitions **in the
> header**, either inside the class or below it in the same file.

Some projects put the out-of-class definitions in a second file, often
named `statistics.tpp` or `statistics_impl.h`, and `#include` it at the
bottom of the header — it's the same thing, just tidier. This course
keeps them in the `.h` file.

[`examples/01_class_template_out_of_class.cpp`](examples/01_class_template_out_of_class.cpp)
shows the syntax.

## Member function templates

A member function can be a template of its own — even in a class that
isn't a template:

```cpp
class Logger {
public:
    template <typename T>
    void log(const std::string& label, const T& value) {
        std::cout << "[" << label << "] " << value << std::endl;
    }
};

Logger log;
log.log("temperature", 28.4);       // T = double
log.log("student", std::string("Ama"));   // T = std::string
log.log("count", 7);                // T = int
```

A class template can have member function templates too. A very useful
case: converting between related instantiations, or accepting any kind
of container:

```cpp
template <typename T>
class Statistics {
public:
    template <typename Container>
    void addAll(const Container& items) {          // works with vector, list, set, array...
        for (const auto& item : items) add(item);
    }
};
```

[`examples/02_member_function_template.cpp`](examples/02_member_function_template.cpp)
shows both.

## Non-type template parameters

Template parameters don't have to be types. They can also be
**compile-time values**, such as an `int`:

```cpp
template <typename T, int Capacity>
class RingBuffer {
private:
    T data[Capacity];        // the size is part of the TYPE - no new[] needed
    int start = 0;
    int count = 0;
public:
    void push(const T& value);
    int capacity() const { return Capacity; }
};

RingBuffer<double, 8> last8Readings;
RingBuffer<int, 100> last100Counts;
```

- The value must be known at **compile time** (a literal or a
  `const`/`constexpr` constant), not a variable read from the user.
- `RingBuffer<double, 8>` and `RingBuffer<double, 16>` are **different
  types** — you can't assign one to the other.
- Because the size is fixed at compile time, the array can be a plain
  member: no heap allocation, and no Rule of Three needed.

You've already used one of these from the standard library:
`std::array<T, N>` is exactly this idea.

[`examples/03_non_type_parameter.cpp`](examples/03_non_type_parameter.cpp)
builds a ring buffer that keeps the last N sensor readings.

## Template specialisation

Sometimes the general recipe is wrong, or inefficient, for one
particular type. You can provide a **specialisation**: a separate
definition used *instead of* the general one for that type.

**Full specialisation of a function template:**

```cpp
template <typename T>
std::string describe(const T& value) {
    return "value: " + std::to_string(value);
}

template <>                                            // "a specialisation..."
std::string describe<bool>(const bool& value) {        // "...for T = bool"
    return value ? "value: yes" : "value: no";
}

template <>
std::string describe<std::string>(const std::string& value) {   // to_string doesn't take strings
    return "value: \"" + value + "\"";
}
```

**Full specialisation of a class template** — a completely separate
class definition for one type:

```cpp
template <typename T>
class Statistics { /* general version: mean, min, max ... */ };

template <>
class Statistics<bool> {             // for bools, "mean" means "fraction that are true"
    int trues = 0, total = 0;
public:
    void add(bool v) { total++; if (v) trues++; }
    double fractionTrue() const { return total == 0 ? 0 : double(trues) / total; }
};
```

A class specialisation shares **nothing** with the general version —
not even its member list. It's a different class that happens to have
the same name.

Use specialisation sparingly: it can surprise readers ("why does
`Statistics<bool>` have no `mean()`?"). Often a plain overloaded
function, or a differently named class, is clearer.

[`examples/04_specialization.cpp`](examples/04_specialization.cpp)
shows both kinds.

## Templates and inheritance

Templates and inheritance combine in two common ways.

**A class template derived from a normal base class** — giving many
type-specific classes a common, polymorphic interface:

```cpp
class Channel {                         // ordinary abstract base (Module 29)
public:
    virtual ~Channel() = default;
    virtual std::string summary() const = 0;
};

template <typename T>
class TypedChannel : public Channel {   // one template, many concrete channel classes
    std::vector<T> samples;
public:
    std::string summary() const override;
};

std::vector<std::unique_ptr<Channel>> channels;
channels.push_back(std::make_unique<TypedChannel<double>>());   // voltages
channels.push_back(std::make_unique<TypedChannel<int>>());      // event counts
channels.push_back(std::make_unique<TypedChannel<bool>>());     // switch states
```

This is a powerful combination: the template saves writing three
almost-identical classes, and the base class lets one loop handle them
all.

**A class derived from a template instantiation:**

```cpp
class TemperatureLog : public Statistics<double> {   // is-a statistics-of-doubles
public:
    bool feverDetected() const { return max() >= 38.0; }
};
```

> **One trap:** inside a class template that derives from *another
> template* (a "dependent base", such as `template <typename T> class
> X : public Base<T>`), the compiler doesn't automatically look in the
> base for names. Write `this->member` (or `Base<T>::member`) to use
> the base's members. The compiler error usually says "there are no
> arguments to 'x' that depend on a template parameter".

[`examples/05_template_inheritance.cpp`](examples/05_template_inheritance.cpp)
shows both patterns, including the `this->` rule.

## Static vs dynamic polymorphism

You now have **two** ways to write code that works with many types:

**Dynamic polymorphism** (`virtual`, Modules 12 and 29): one function
handles any type derived from a base, chosen **at runtime**.

```cpp
void printArea(const Shape& s) { std::cout << s.area(); }   // works for any Shape subclass
```

**Static polymorphism** (templates): the compiler generates a separate
version for each type, chosen **at compile time**. The types need no
common base class — they only need to support the operations used.

```cpp
template <typename S>
void printArea(const S& s) { std::cout << s.area(); }       // works for any type with area()
```

| | Dynamic (`virtual`) | Static (templates) |
|---|---|---|
| Decided | at runtime | at compile time |
| Types must share a base class? | yes | no — just the right operations |
| Mixed collection (`vector<unique_ptr<Shape>>`)? | **yes** | no — each instantiation is a different type |
| Can add new types without recompiling the code that uses them? | yes | no |
| Speed | one indirect call per virtual call | calls can be inlined; no vtable |
| Error messages | short and clear | historically long (improved by concepts, below) |
| Code size | one copy of the function | one copy per type used |

The rule of thumb: **if you need a mixed collection of objects decided
at runtime, use virtual functions. If the types are all known at
compile time and you want generic code with no runtime cost, use
templates.** Large programs commonly use both.

## A first look at CRTP

There's a well-known idiom that gives you some benefits of inheritance
(shared code in a base class) with static polymorphism. It has an
odd-sounding name — the **Curiously Recurring Template Pattern** — because
a class derives from a template **instantiated with itself**:

```cpp
template <typename Derived>
class Printable {
public:
    void print() const {
        // static_cast to the derived type: safe here, because Derived really
        // IS the class that derived from us
        const Derived& self = static_cast<const Derived&>(*this);
        std::cout << "[" << self.label() << "] " << self.value() << std::endl;
    }
};

class Reading : public Printable<Reading> {      // "curiously recurring"
public:
    std::string label() const { return "reading"; }
    double value() const { return 21.5; }
};

Reading r;
r.print();     // calls Reading::label and Reading::value - no virtual, decided at compile time
```

The base class supplies the shared `print()`; each derived class
supplies `label()` and `value()`; and everything is resolved at compile
time. You won't need to write CRTP often at this stage, but you'll meet
it in libraries — recognising the shape `class X : public Base<X>` is
the goal.

[`examples/06_static_vs_dynamic.cpp`](examples/06_static_vs_dynamic.cpp)
writes the same "describe a sensor" feature three ways: `virtual`,
a function template, and CRTP.

## C++20 concepts: saying what a template needs

A template silently assumes things about `T`: that it can be added,
compared, printed, or has an `area()` method. If you use a type that
doesn't fit, the error appears **deep inside** the template's code
(Module 18 warned you about this), often as pages of text.

**Concepts** (C++20) let you state those assumptions up front:

```cpp
#include <concepts>

template <typename T>
concept HasArea = requires(const T& shape) {
    { shape.area() } -> std::convertible_to<double>;   // "shape.area() must compile and give a number"
};

template <HasArea S>                // only types satisfying HasArea are allowed
double totalArea(const std::vector<S>& shapes) {
    double total = 0;
    for (const S& s : shapes) total += s.area();
    return total;
}
```

- A **concept** is a named, compile-time yes/no test on a type.
- A **`requires` expression** lists operations that must compile (and,
  optionally, what their results must convert to).
- Use a concept in place of `typename` (`template <HasArea S>`) to
  **constrain** the template.

The standard library provides many ready-made concepts in
`<concepts>`, such as `std::integral`, `std::floating_point`,
`std::totally_ordered`, and `std::copyable`:

```cpp
template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template <Numeric T>
class Statistics { /* ... */ };

Statistics<double> ok;
Statistics<std::string> nope;   // ERROR: "template constraint failure ... requires Numeric<T> ...
                                //         note: constraints not satisfied"
```

Now the error message names the **requirement that failed**, at the
line where you used the wrong type, instead of an obscure error inside
`mean()`.

> **This needs C++20:** compile with `-std=c++20`.

[`examples/07_concepts.cpp`](examples/07_concepts.cpp) defines and uses
several concepts.

## Common beginner mistakes

- Putting a template's member function definitions in a `.cpp` file
  (→ `undefined reference` at link time). Keep them in the header.
- Forgetting the `template <typename T>` line, or writing
  `Statistics::` instead of `Statistics<T>::`, on an out-of-class
  definition.
- Using a variable for a non-type template argument —
  `RingBuffer<double, n>` only works if `n` is a compile-time constant.
- Expecting `RingBuffer<double, 8>` and `RingBuffer<double, 16>` to be
  interchangeable — they're different types.
- Forgetting `this->` when using a member of a templated base class.
- Choosing templates when you need a runtime-mixed collection (use
  `virtual`), or `virtual` when everything is known at compile time and
  speed matters (consider templates).
- Over-specialising: a specialisation that behaves very differently
  from the general template surprises readers.
- Using concepts without `-std=c++20` and `#include <concepts>`.

## Try it yourself

1. Work through [`examples/`](examples/). Use `-std=c++20` for
   `07_concepts.cpp`.
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md), continuing your
   track.
4. Commit:

   ```bash
   git add 32-templates-meet-oop
   git commit -m "Complete Module 32: templates meet OOP"
   git push
   ```

Next: **[Module 33 — SOLID Principles & Clean Design](../33-solid-principles/README.md)**.
