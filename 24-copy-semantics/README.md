# Module 24 — Copy Semantics

Module 23 ended with a warning: an RAII class that owns heap memory
works perfectly — until you copy it. Then two objects end up sharing
the same memory, and both try to `delete` it.

This module explains exactly what "copying an object" means in C++,
when it happens (far more often than you might think), and how to take
control of it. By the end you'll know:

- the four places copies happen
- what the compiler-generated copy does: **memberwise copy**
- **shallow** vs **deep** copies, and why shallow copies of owning
  pointers are dangerous
- how to write a **copy constructor** and a **copy assignment
  operator**
- the **Rule of Three**
- how to make a class **non-copyable** with `= delete`, and how to ask
  for the default behaviour explicitly with `= default`
- the **copy-and-swap** idiom
- the best rule of all: designing classes so you **don't need to
  write any of this**

## When do copies happen?

A copy is made whenever a new object is created **from an existing
object of the same type**. That happens in four everyday situations:

```cpp
Gradebook a("Maths");

Gradebook b = a;            // 1. initialising a new variable from an existing one
Gradebook c(a);             //    (same thing, different spelling)

void print(Gradebook g);    // 2. passing BY VALUE
print(a);                   //    -> g is a copy of a

Gradebook makeCopy() {
    Gradebook local("Physics");
    return local;           // 3. returning by value (often optimised away - Module 25)
}

std::vector<Gradebook> books;
books.push_back(a);         // 4. putting it in a container - the vector stores its own copy
```

And one more that looks similar but is different: **assigning to an
object that already exists**:

```cpp
Gradebook d("Science");
d = a;                      // NOT a new object - d already exists. This is copy ASSIGNMENT.
```

C++ treats these as two different operations:

| Code | Operation | Special member function |
|---|---|---|
| `Gradebook b = a;` / `Gradebook b(a);` / pass by value / `push_back` | Make a **new** object as a copy | **copy constructor** |
| `d = a;` (`d` already exists) | Replace an **existing** object's contents | **copy assignment operator** |

[`examples/01_when_copies_happen.cpp`](examples/01_when_copies_happen.cpp)
traces every one of these so you can see the copy constructor and copy
assignment running.

## What the compiler does by default: memberwise copy

If you don't write a copy constructor or copy assignment operator, the
compiler writes them for you. Its version copies **each member, one by
one**, using that member's own copy:

- an `int` or `double` is copied as a number
- a `std::string` is copied using `std::string`'s copy (a new, separate
  string with the same characters)
- a `std::vector` is copied using `std::vector`'s copy (a new,
  separate vector with copies of every element)
- a **pointer** is copied as a pointer — that is, as an **address**

For classes made of numbers, strings, and vectors, the default is
exactly right, and you should not write your own. The trouble is only
with that last bullet.

## Shallow copy vs deep copy

```cpp
class SampleBuffer {
private:
    double* data;     // points to an array on the heap
    int size;
public:
    explicit SampleBuffer(int n) : data(new double[n]), size(n) {}
    ~SampleBuffer() { delete[] data; }
};

SampleBuffer a(100);
SampleBuffer b = a;   // default memberwise copy
```

The default copy copies `data` — **the address** — not the array it
points to. After the copy:

```
   a.data ──┐
            ├──>  [ 100 doubles on the heap ]
   b.data ──┘
```

This is a **shallow copy**: the two objects *share* one array. That
causes three bugs:

1. **Changes leak between objects.** Writing a sample through `b`
   changes what `a` sees.
2. **Double delete.** When `b` dies, its destructor frees the array.
   When `a` dies, its destructor frees the *same* array again —
   undefined behaviour, usually a crash.
3. **Dangling pointer.** Between those two deaths, `a.data` points to
   memory that has already been freed.

What we want is a **deep copy**: `b` gets its *own* new array,
containing copies of `a`'s values:

```
   a.data ──>  [ 100 doubles ]
   b.data ──>  [ 100 doubles, copied from a's ]
```

[`examples/02_shallow_copy_problem.cpp`](examples/02_shallow_copy_problem.cpp)
demonstrates bug 1 safely (it deliberately has no destructor, so it
leaks instead of crashing), and explains bug 2 in comments.

**Rule:** if a class holds a raw pointer that **owns** a resource (it's
responsible for deleting it), the default copy is wrong, and you must
take control.

## The copy constructor

The copy constructor is a constructor whose parameter is a **`const`
reference to the same class**:

```cpp
class SampleBuffer {
private:
    double* data;
    int size;
public:
    explicit SampleBuffer(int n) : data(new double[n]), size(n) {}

    // Copy constructor: build a NEW buffer as a deep copy of other.
    SampleBuffer(const SampleBuffer& other)
        : data(new double[other.size]), size(other.size) {
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    ~SampleBuffer() { delete[] data; }
};
```

- It **must** take its parameter by reference. If it took it by value,
  calling it would require a copy... which would call the copy
  constructor... forever. (The compiler refuses to compile that.)
- It's `const` because copying something shouldn't change it.
- Notice it can read `other.data` and `other.size` even though they're
  `private`. Access control is **per class**, not per object: any
  `SampleBuffer` method may use any `SampleBuffer`'s private members.

[`examples/03_deep_copy_constructor.cpp`](examples/03_deep_copy_constructor.cpp)
shows the copies are now independent, and that both destructors run
safely.

## The copy assignment operator

Assignment is harder than construction, because the left-hand object
**already exists** and already owns an array. A correct assignment must:

1. Handle **self-assignment** (`a = a;`) safely.
2. Free (or reuse) the memory the object already owns — otherwise it
   leaks.
3. Make a deep copy of the right-hand side's data.
4. Return `*this` by reference, so that `a = b = c;` works like it does
   for `int`s.

```cpp
SampleBuffer& operator=(const SampleBuffer& other) {
    if (this == &other) {
        return *this;                       // 1. self-assignment: nothing to do
    }
    double* newData = new double[other.size];   // 3. copy FIRST...
    for (int i = 0; i < other.size; i++) {
        newData[i] = other.data[i];
    }
    delete[] data;                          // 2. ...THEN free the old array
    data = newData;
    size = other.size;
    return *this;                           // 4.
}
```

Why copy first and free second? If `new` fails (it can — it throws an
exception when memory runs out, Module 31), we haven't yet destroyed
our old data, so the object is left unchanged instead of broken.

This is the same `operator=` syntax you used in Module 13 for other
operators — copy assignment is just a very special operator overload.

[`examples/04_copy_assignment.cpp`](examples/04_copy_assignment.cpp)
traces copy assignment, including self-assignment.

## The Rule of Three

Look at what `SampleBuffer` needed:

1. a **destructor** (to free the array),
2. a **copy constructor** (to deep-copy into a new object),
3. a **copy assignment operator** (to deep-copy into an existing one).

These three always go together, and that observation has a name:

> **The Rule of Three:** if a class needs a user-written destructor,
> copy constructor, or copy assignment operator, it almost certainly
> needs **all three**.

The logic: you only write a destructor when the class owns a resource
that needs releasing — and if it owns a resource, the default
memberwise copy (which would share it) is wrong in both copy
operations. Whenever you write a destructor that `delete`s something,
treat it as an alarm bell: "what happens when this is copied?"

(Module 25 extends this to the **Rule of Five**.)

## Copy-and-swap (an elegant alternative)

The assignment operator above is correct, but it repeats the copying
loop from the copy constructor. The **copy-and-swap idiom** reuses the
copy constructor instead:

```cpp
#include <utility>   // std::swap

SampleBuffer& operator=(SampleBuffer other) {   // note: BY VALUE - a copy is made here
    std::swap(data, other.data);                // take other's data...
    std::swap(size, other.size);                // ...and give it our old data
    return *this;
}   // other dies here, taking our OLD data with it - its destructor frees it
```

It's short, it's automatically safe for self-assignment, and if the
copy fails, nothing has changed. You'll see this idiom in real code;
recognise it. Either version is acceptable in this course.

## Choosing *not* to be copyable: `= delete`

Some things **shouldn't** be copied at all. What would it mean to copy
a `SupplyGuard` from Module 23 — two guards both switching off the same
power supply? Or a `SessionLog` that owns an open file?

You can tell the compiler to forbid copying:

```cpp
class SupplyGuard {
public:
    SupplyGuard(PowerSupply& psu, double volts);
    ~SupplyGuard();

    SupplyGuard(const SupplyGuard&) = delete;             // no copy construction
    SupplyGuard& operator=(const SupplyGuard&) = delete;  // no copy assignment
};
```

Now `SupplyGuard g2 = g1;` is a **compile error** with a clear message
("use of deleted function"), instead of a hidden runtime bug. Making a
class non-copyable is a perfectly good — often the best — answer to the
Rule of Three. [`examples/05_non_copyable.cpp`](examples/05_non_copyable.cpp)
shows it.

The opposite is `= default`, which means "please generate the normal
version for me":

```cpp
Point(const Point&) = default;
```

It's useful for documenting that you *thought about* copying and the
default is correct — and it becomes important in Module 25.

## The best answer: let the members do the work (the Rule of Zero)

Here's the most important lesson of this module. Look at this class:

```cpp
class SampleBuffer {
private:
    std::vector<double> data;
public:
    explicit SampleBuffer(int n) : data(n) {}
};
```

It has **no** destructor, **no** copy constructor, **no** copy
assignment operator — and copying it is **completely correct**. The
default memberwise copy copies the `std::vector`, and `std::vector`
already knows how to deep-copy itself and free its own memory.

> **The Rule of Zero:** design your classes so that every member
> manages itself (`std::string`, `std::vector`, other RAII classes, and
> — from Module 26 — smart pointers). Then you need to write **none**
> of the special member functions, and the compiler-generated ones are
> correct.

So why learn the Rule of Three at all? Because:

- someone has to write the classes that *do* manage raw resources
  (`std::vector` itself is one!), and occasionally that someone is you;
- you'll read and maintain older code written before these tools
  existed;
- understanding what can go wrong is what lets you *recognise* a
  dangerous class when you see one.

But in your own new code: **prefer the Rule of Zero.** Reach for a
`std::vector` before a `new[]`.

## Common beginner mistakes

- Writing a destructor that `delete`s a member, and forgetting the
  copy constructor and copy assignment (breaking the Rule of Three).
- Copy constructor taking its parameter **by value** — it must be
  `const ClassName&`.
- Forgetting the self-assignment check in a hand-written `operator=`
  (`a = a;` then deletes its own data before copying it).
- Freeing the old data **before** making the new copy in `operator=`.
- Forgetting to `return *this;` from `operator=`.
- Confusing `Gradebook b = a;` (copy **construction** — `b` is new)
  with `b = a;` (copy **assignment** — `b` already existed).
- Passing large objects by value "by accident" (forgetting the `&`),
  causing an expensive copy every call. Use `const T&` for parameters
  you only read.
- Writing all three special functions for a class whose members are
  already `std::string`/`std::vector` — unnecessary and a source of
  bugs. Follow the Rule of Zero.

## Try it yourself

1. Work through [`examples/`](examples/). Predict which special member
   function runs on each line before running.
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md), continuing your
   track.
4. Commit:

   ```bash
   git add 24-copy-semantics
   git commit -m "Complete Module 24: copy semantics and the Rule of Three"
   git push
   ```

Next: **[Module 25 — Move Semantics](../25-move-semantics/README.md)**.
