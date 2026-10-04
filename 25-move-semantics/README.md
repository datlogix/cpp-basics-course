# Module 25 — Move Semantics

Module 24 made copies **correct**. This module makes them **cheap** —
or, more precisely, shows you how to avoid copying at all when a copy
isn't really needed.

Imagine a `SampleBuffer` holding a million readings. Copying it means
allocating a million new `double`s and copying every one. Now imagine
the object you're copying from is about to be thrown away anyway —
a temporary, or a local variable at the end of its function. Copying
a million values out of something that's about to be destroyed is pure
waste. It would be much faster to just **take its array**: copy one
pointer, and leave the dying object empty.

That's a **move**. This module covers:

- **lvalues** and **rvalues** — "things with a name" vs "temporaries"
- **rvalue references** (`&&`)
- the **move constructor** and **move assignment operator**
- **`std::move`** — what it does (and, importantly, what it doesn't)
- the **moved-from** state
- **`noexcept`**, and why `std::vector` cares about it
- the **Rule of Five**, and the Rule of Zero revisited
- when the compiler moves (or skips the copy entirely) for you

## Copying vs moving — the idea

Think of a box of exam scripts being handed from one teacher to another.

- **Copy:** photocopy every script, give the copies to the new teacher.
  Both teachers now have a full box. Slow, but the first teacher still
  has theirs.
- **Move:** hand over the box. Instant. The first teacher now has an
  empty desk — which is fine, *if they were about to go home anyway*.

In code, for a class that owns a heap array:

```
COPY:   source.data ──> [ 1,000,000 values ]
        dest.data   ──> [ 1,000,000 values, copied one by one ]   (slow)

MOVE:   dest.data   ──> [ 1,000,000 values ]   (the SAME array - one pointer copied)
        source.data ──> nullptr                (source is left empty but valid)
```

A move is only safe when **nobody will use the source's old contents
again**. So the key question is: how does C++ know when that's true?

## lvalues and rvalues

Every expression in C++ belongs to a category. The two you need are:

- An **lvalue** has a **name** (or otherwise an identity you can refer
  to again). Variables are lvalues. You can take their address with
  `&`. Historically: something that can appear on the **l**eft of `=`.
- An **rvalue** is a **temporary** — a value with no name that is about
  to disappear at the end of the statement. Historically: something
  that can only appear on the **r**ight of `=`.

```cpp
int x = 5;               // x is an lvalue; 5 is an rvalue
int y = x + 1;           // x + 1 is an rvalue (a temporary result)

std::string a = "Ama";
std::string b = a;               // a is an lvalue - it lives on after this line
std::string c = a + " Mensah";   // a + " Mensah" is an rvalue - a temporary
SampleBuffer s = makeBuffer();   // the returned value is an rvalue
```

The rule that makes moves safe falls straight out of this: **an rvalue
can't be used again** (it has no name to refer to it by), so it is
always safe to move from it.

## Rvalue references: `&&`

You've used ordinary references (`T&`) since Module 7. These are
**lvalue references** — they bind to things with names. C++11 added a
second kind:

```cpp
void take(std::string& s);         // binds to lvalues only
void take(const std::string& s);   // binds to anything (read-only)
void take(std::string&& s);        // binds to RVALUES only - temporaries
```

A function taking `T&&` is saying: "give me something that's about to
be thrown away, and I'll feel free to steal from it." Overloading on
`const T&` vs `T&&` lets a class do one thing for lvalues (copy) and
another for rvalues (move) — the compiler picks the right one
automatically.

## The move constructor

```cpp
class SampleBuffer {
private:
    double* data;
    int size;
public:
    // ... constructor, copy constructor, copy assignment, destructor ...

    // Move constructor: steal other's array instead of copying it.
    SampleBuffer(SampleBuffer&& other) noexcept
        : data(other.data), size(other.size) {
        other.data = nullptr;   // leave other EMPTY...
        other.size = 0;         // ...but still VALID
    }
};
```

Three things to notice:

1. The parameter is `SampleBuffer&&` — **not** `const`, because we
   modify the source.
2. We copy the **pointer**, then set the source's pointer to `nullptr`.
   This is essential: when `other` is later destroyed, its destructor
   runs `delete[] data` — and `delete[] nullptr` is defined to do
   nothing. Without that line, both objects would delete the same array
   (the Module 24 double-delete bug, back again).
3. It's marked `noexcept` — explained below.

## The move assignment operator

Move assignment is to move construction what copy assignment is to copy
construction: the target **already exists** and already owns something,
which must be freed.

```cpp
SampleBuffer& operator=(SampleBuffer&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    delete[] data;          // free what we currently own
    data = other.data;      // steal
    size = other.size;
    other.data = nullptr;   // leave the source empty but valid
    other.size = 0;
    return *this;
}
```

[`examples/02_move_constructor.cpp`](examples/02_move_constructor.cpp)
traces copies and moves side by side, printing the array addresses so
you can see a move really does hand over the same memory.

## `std::move` — permission to move from an lvalue

Sometimes *you* know an lvalue won't be used again, even though the
compiler can't tell:

```cpp
SampleBuffer recording(1000000);
// ... fill it ...
archive.push_back(recording);   // COPIES a million values - recording is an lvalue
// ... recording is never used again ...
```

`std::move` (from `<utility>`) lets you say "treat this as an rvalue —
I give permission to move from it":

```cpp
archive.push_back(std::move(recording));   // MOVES - just a pointer handed over
```

The name is misleading, so read this twice:

> **`std::move` doesn't move anything.** It's just a cast — it changes
> the *category* of the expression to rvalue, so that the *move*
> constructor/assignment is chosen instead of the *copy* one. The actual
> moving is done by those functions.

### The moved-from state

After `std::move(recording)` has been used to move from it, `recording`
is in a **valid but unspecified** state. For our class it's empty
(`data == nullptr`). For standard library types like `std::string` and
`std::vector`, it's usually empty too, but the standard doesn't
promise exactly what's left.

What you **may** do with a moved-from object:

- let it be destroyed (always safe),
- assign a new value to it (`recording = SampleBuffer(500);`).

What you **must not** do: rely on its old contents. Treat "moved from"
like "this box has been handed over" — don't reach into it.

[`examples/03_std_move.cpp`](examples/03_std_move.cpp) demonstrates
`std::move` with both `std::string` and our own class.

## When moves happen automatically

You often get moves without writing `std::move` at all:

- **Temporaries.** `SampleBuffer s = SampleBuffer(100);` or
  `v.push_back(SampleBuffer(100));` — the argument is an rvalue, so the
  move constructor is chosen automatically.
- **Returning a local variable.** `return localBuffer;` will move (if it
  doesn't skip the copy entirely — see next point). **Don't** write
  `return std::move(localBuffer);` — it can actually *prevent* the
  optimisation below.
- **Copy elision.** Often the compiler doesn't copy *or* move at all: it
  builds the returned object directly in the caller's variable. You saw
  this in Module 24's first example, where returning by value printed no
  copy. Since C++17 this is *guaranteed* when you return a temporary
  (`return SampleBuffer(100);`).

## `noexcept` and `std::vector`

When a `std::vector` runs out of space, it allocates a bigger array
and transfers every element across. It would love to **move** them
(fast), but there's a catch: if a move threw an exception half-way
through, some elements would be in the new array and some in the old
one — the vector couldn't put itself back together.

So `std::vector` only moves elements during growth if their move
constructor is marked **`noexcept`** — a promise that it never throws
an exception. Otherwise it plays safe and **copies** every element.

[`examples/04_noexcept_vector.cpp`](examples/04_noexcept_vector.cpp)
proves this: the same class, with and without `noexcept`, causes very
different numbers of copies as a vector grows.

**Rule:** always mark your move constructor and move assignment
`noexcept`. They only shuffle pointers and numbers, so they genuinely
can't fail — say so.

## The Rule of Five

With moves added, the special member functions that manage a resource
become five:

1. destructor
2. copy constructor
3. copy assignment operator
4. move constructor
5. move assignment operator

> **The Rule of Five:** if a class needs to define any of these, it
> should think carefully about all five — define them, `= default` them,
> or `= delete` them.

One trap: if you write a destructor or a copy operation, the compiler
**stops generating the move operations for you**. The class still
works — moves silently fall back to copies — but you lose the speed.
That's why Module 24's `SampleBuffer` copied every time it was pushed
into a vector.

A **move-only** type is also common and useful: delete the copies, keep
the moves. A unique resource — an open file, a hardware connection —
can't sensibly be *duplicated*, but can perfectly well be *handed
over*. (Module 26's `std::unique_ptr` is exactly this.)

```cpp
class SerialPort {
public:
    SerialPort(const SerialPort&) = delete;
    SerialPort& operator=(const SerialPort&) = delete;
    SerialPort(SerialPort&&) noexcept;              // can be handed over
    SerialPort& operator=(SerialPort&&) noexcept;
    ~SerialPort();
};
```

## The Rule of Zero, again

Everything in Module 24's "Rule of Zero" section applies twice over
now. A class whose members are `std::string`, `std::vector`, and other
well-behaved types gets a correct, efficient **move** constructor and
move assignment *for free* — the compiler moves each member, and
`std::vector`'s own move is just a pointer swap.

[`examples/05_rule_of_zero.cpp`](examples/05_rule_of_zero.cpp) shows a
`std::vector`-based class moving at full speed with zero special member
functions written.

**In your own code: prefer the Rule of Zero.** Write the Rule of Five
only for a class whose entire job is to manage one raw resource — and
then keep that class small, so everything else can follow the Rule of
Zero by using it as a member.

## Common beginner mistakes

- Forgetting to set the source's pointer to `nullptr` in a move
  operation — the source's destructor then frees the stolen array.
- Marking the move constructor parameter `const` (`const T&&`) — you
  can't modify (steal from) a `const` object, so it silently copies.
- Forgetting `noexcept` on move operations, so `std::vector` copies
  instead of moving.
- Believing `std::move` moves something by itself. It's a cast; the
  move constructor/assignment does the work.
- Using an object after moving from it, expecting its old value.
- Writing `return std::move(local);` — just write `return local;`.
- Writing a destructor and assuming the class still has (fast) move
  operations. It doesn't, unless you declare them.
- `std::move` on a `const` object — it can't be moved from, so it's
  quietly copied.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md), continuing your
   track.
4. Commit:

   ```bash
   git add 25-move-semantics
   git commit -m "Complete Module 25: move semantics and the Rule of Five"
   git push
   ```

Next: **[Module 26 — Smart Pointers & Ownership](../26-smart-pointers/README.md)**.
