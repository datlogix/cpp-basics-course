# Module 10 — Pointers & Dynamic Memory

Welcome to **Part 2: Intermediate C++**. Part 1 got you to a real, working
program. Part 2 opens up the ideas that let you build larger, more
efficient, more realistic software — starting with the concept most
beginners find intimidating and most professionals consider fundamental:
**the pointer**.

You already used one pointer, narrowly, in the Part 1 capstone
(`Student* findStudent(...)`, returning `nullptr` when nothing was
found). This module generalizes that into a real, working understanding
of what a pointer actually is.

## What a pointer actually is

Every variable lives somewhere in your computer's memory, at a numeric
**address**. A pointer is simply a variable that *stores an address*
instead of storing a value directly.

```cpp
int age = 25;
int* agePtr = &age;   // agePtr stores the ADDRESS of age

std::cout << age << std::endl;      // 25            (the value)
std::cout << &age << std::endl;     // 0x7ffee3a1c... (the address)
std::cout << agePtr << std::endl;   // 0x7ffee3a1c... (same address)
std::cout << *agePtr << std::endl;  // 25             (the value AT that address)
```

Two new operators, and they are opposites of each other:

- `&x` — "address-of": gives you the address where `x` lives.
- `*p` — "dereference": given an address, gives you the value stored
  there.

```cpp
*agePtr = 30;              // write 30 to the address agePtr points to
std::cout << age << std::endl;  // 30 — age itself changed!
```

This should feel familiar: it's the exact same mechanism behind pass by
reference (Module 7) and the capstone's `Student*` — a reference and a
pointer both let code reach across function boundaries and touch the
*original* variable, not a copy. A reference is a pointer with training
wheels: safer syntax, but it can never be reseated or set to "nothing."
A raw pointer is more flexible and more dangerous.

## `nullptr` — a pointer that points to nothing

```cpp
int* p = nullptr;
```

You met this in the Part 1 capstone as "not found." More generally,
`nullptr` is the safe way to say "this pointer isn't valid right now."
**Dereferencing a null pointer** (`*p` when `p` is `nullptr`) is
undefined behavior — typically an immediate crash. Always check before
dereferencing:

```cpp
if (p != nullptr) {
    std::cout << *p << std::endl;
}
```

## Dynamic memory: `new` and `delete`

Every variable you've declared so far (`int x;`, `Student s;`) is
allocated **automatically** — the compiler reserves its memory the
moment it comes into scope, and frees it the moment that scope ends.
This is convenient but has one hard limit: **the size must be known at
compile time.**

Sometimes you don't know how much memory you need until the program is
*running* — e.g., "allocate space for exactly as many sensor readings as
the user asks for, right now." That's what `new` is for:

```cpp
int n;
std::cout << "How many readings? ";
std::cin >> n;

double* readings = new double[n];   // allocated on the HEAP, size decided at runtime

for (int i = 0; i < n; i++) {
    readings[i] = 0.0;
}

// ... use readings[i] like a normal array ...

delete[] readings;   // give the memory back when you're done
readings = nullptr;  // good practice: avoid an accidental dangling pointer
```

- `new double[n]` asks the operating system for enough memory to hold
  `n` doubles and returns a pointer to the first one.
- `delete[] readings;` **must** be called exactly once, when you're
  finished, to give that memory back. Forgetting this is called a
  **memory leak** — the memory stays reserved for the rest of the
  program's life, unusable by anything else.
- Use `delete[]` (with brackets) for arrays allocated with `new[]`, and
  plain `delete` (no brackets) for a single object allocated with `new`.
  Mismatching them is undefined behavior.

## The three classic pointer bugs

Naming these explicitly now saves real debugging pain later:

1. **Memory leak** — calling `new` without a matching `delete`. The
   program's memory usage grows and never shrinks.
2. **Dangling pointer** — using a pointer *after* its memory has been
   freed. The address is no longer valid, but the pointer variable still
   holds it, looking deceptively normal.
3. **Double free** — calling `delete` twice on the same pointer.
   Undefined behavior, often a crash.

```cpp
double* data = new double[10];
delete[] data;
// data is now a DANGLING pointer - the memory is gone
data[0] = 5.0;      // BUG: writing through a dangling pointer
delete[] data;      // BUG: double free
```

The defensive habit: set a pointer to `nullptr` immediately after
deleting it. `delete nullptr;` is explicitly safe and does nothing, so
this also protects against accidental double frees.

## A brief, honest note on smart pointers

Modern C++ has tools (`std::unique_ptr`, `std::shared_ptr`, from
`<memory>`) that manage `delete` for you automatically, eliminating most
leaks and dangling pointers by design. They are the recommended default
in real production code. This course teaches raw `new`/`delete` first,
deliberately, because understanding what's happening underneath is what
makes smart pointers make sense later — treat them as the natural next
step after this module, not a replacement for understanding this one.

## Pointers and arrays: a close relationship

An array name, used by itself, *decays* into a pointer to its first
element — this is why array indexing and pointer arithmetic are closely
related:

```cpp
int scores[3] = {90, 85, 77};
int* p = scores;         // p now points to scores[0]

std::cout << *p << std::endl;       // 90  (same as scores[0])
std::cout << *(p + 1) << std::endl; // 85  (same as scores[1])
std::cout << p[2] << std::endl;     // 77  (pointer indexing works too)
```

You won't need to lean on pointer arithmetic directly very often — `[ ]`
indexing and `std::vector` remain your default tools — but recognizing
this relationship demystifies a lot of C++ code you'll read elsewhere.

## Common beginner mistakes

- Dereferencing an uninitialized or `nullptr` pointer.
- Forgetting `delete[]` after `new[]` (memory leak).
- Using `delete` (no brackets) on an array, or `delete[]` on a single
  object.
- Using a pointer after it's been deleted (dangling pointer) without
  setting it to `nullptr` first.
- Confusing `*` in a declaration (`int* p` — "p is a pointer to int")
  with `*` in an expression (`*p` — "the value p points to"). Same
  symbol, two different meanings depending on context.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — pick the Generic,
   Electrical/Electronic Engineering, or Biomedical Engineering track.
4. Commit:

   ```bash
   git add 10-pointers-dynamic-memory
   git commit -m "Complete Module 10: pointers and dynamic memory"
   git push
   ```

Next: **[Module 11 — Inheritance](../11-inheritance/README.md)**.
