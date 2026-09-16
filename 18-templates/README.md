# Module 18 — Templates

You've used templates constantly without writing one: `std::vector<int>`,
`std::vector<double>`, `std::map<std::string, double>` are all the
**same** underlying code, generated for different types. This module
teaches you to write that kind of generic, type-parameterized code
yourself.

## The problem templates solve

Recall Module 7's overloading example:

```cpp
int add(int a, int b) { return a + b; }
double add(double a, double b) { return a + b; }
```

The logic is *identical* — only the type changes. Overloading works,
but you'd need to retype the same function for every type you ever
need. A **function template** writes the logic exactly once, letting
the compiler generate the right version for whatever type you actually
call it with.

## Function templates

```cpp
template <typename T>
T maxOf(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    std::cout << maxOf(3, 7) << std::endl;         // T = int
    std::cout << maxOf(3.5, 2.1) << std::endl;      // T = double
    std::cout << maxOf(std::string("a"), std::string("b")) << std::endl; // T = std::string
    return 0;
}
```

- `template <typename T>` — declares that this function is generic over
  some type, named `T` for now (any name works; `T` is just convention).
- The compiler looks at how you *call* `maxOf` and generates a real,
  concrete version for that specific type automatically — this happens
  at compile time, with no runtime cost at all.
- `T` must support whatever operations the template body uses — here,
  `>` — so `maxOf` works for any type where `>` is meaningful (all the
  built-in numeric types, and any custom class that overloaded `>`,
  tying directly back to Module 13).

## Class templates

The same idea applies to whole classes — this is exactly how
`std::vector<T>` itself is built:

```cpp
template <typename T>
class Pair {
private:
    T first;
    T second;

public:
    Pair(T a, T b) : first(a), second(b) {}

    T getFirst() const { return first; }
    T getSecond() const { return second; }
    T sum() const { return first + second; }
};

int main() {
    Pair<int> intPair(3, 4);
    std::cout << intPair.sum() << std::endl;        // 7

    Pair<double> doublePair(1.5, 2.5);
    std::cout << doublePair.sum() << std::endl;      // 4

    return 0;
}
```

- `Pair<int>` and `Pair<double>` are two entirely separate, real classes
  the compiler generates from the one template — same relationship as
  `int add` / `double add` from the overloading example, but written
  once.
- Every method defined inside a class template is implicitly a template
  too, using the same `T`.

## A practical example: generic statistics

```cpp
template <typename T>
T computeSum(std::vector<T> values) {
    T total = T(); // zero-initialize, whatever T is (0, 0.0, etc.)
    for (T v : values) {
        total += v;
    }
    return total;
}

template <typename T>
double computeAverage(std::vector<T> values) {
    return static_cast<double>(computeSum(values)) / values.size();
}
```

`computeAverage` now works for a `vector<int>` of sample counts *or* a
`vector<double>` of voltage readings, with no duplicated code — this is
the direct generalization of the `average()` function you first wrote,
type-specific, back in Module 6.

## Templates with more than one type parameter

```cpp
template <typename K, typename V>
class KeyValue {
private:
    K key;
    V value;
public:
    KeyValue(K k, V v) : key(k), value(v) {}
    void print() {
        std::cout << key << ": " << value << std::endl;
    }
};

KeyValue<std::string, double> reading("R1", 220.0);
reading.print();
```

This is precisely `std::map<K, V>`'s own shape — two independent type
parameters, one for the key, one for the value.

## When templates go wrong: errors appear where the type is used

A template error often doesn't point at the template definition — it
points at the **specific call site** where an unsupported type was
used, sometimes with a long, intimidating error message. The practical
approach: read the error for the actual type mentioned and the actual
operation that failed (often near the top or bottom of a long message),
rather than trying to parse every line. This is the same "read the
compiler error calmly" skill from Module 1, applied to a more verbose
case.

## Common beginner mistakes

- Forgetting `template <typename T>` immediately above *every* function
  or class definition that uses `T` — it doesn't carry over between
  declarations.
- Calling a template function/class with a type that doesn't support an
  operation the template body needs (e.g. `maxOf` on a type with no
  `>`), and being confused by the resulting error.
- Confusing a template *parameter* (`T`, decided when you use the
  template) with a regular function *parameter* (decided by the actual
  argument value) — they're independent: `T` decides the type, the
  parameters still hold values of that type.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — pick the Generic,
   EE, or Biomedical track.
4. Commit:

   ```bash
   git add 18-templates
   git commit -m "Complete Module 18: templates"
   git push
   ```

Next: **[Module 19 — Capstone Project 2](../19-capstone-project-2/README.md)**.
