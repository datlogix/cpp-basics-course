# Module 31 — Exceptions in Class Design

Module 15 taught the mechanics of exceptions: `throw`, `try`, `catch`,
catching specific types before `std::exception`, and validating a
class's invariant in its constructor. Since then you've learned about
object lifetimes (Module 23), copying and moving (24–25), smart
pointers (26), and class hierarchies (27–29).

This module puts those together. Exceptions don't just affect the
function that throws — they pass *through* objects, constructors,
destructors, and half-finished operations. Designing classes that stay
**correct when an exception happens** is one of the most important
skills in professional C++:

- designing your own **exception class hierarchy**
- exceptions that carry **extra information**
- what happens when a **constructor throws**
- why **destructors must never throw** (and `noexcept`)
- the three **exception-safety guarantees**: basic, strong, no-throw
- how **RAII** makes code exception-safe almost for free
- **rethrowing** and **translating** exceptions between layers
- `noexcept` revisited, and when to use it

## A quick recap

```cpp
try {
    double dose = calculateDose(weightKg);   // might throw
    std::cout << dose;
} catch (const std::invalid_argument& e) {   // most specific first
    std::cout << "Bad input: " << e.what() << std::endl;
} catch (const std::exception& e) {          // safety net
    std::cout << "Error: " << e.what() << std::endl;
}
```

- `throw` stops the current function immediately and starts
  **unwinding the stack**: leaving each function and block in turn,
  destroying their local objects (Module 23!), until a matching `catch`
  is found.
- Catch **by `const` reference** — catching by value would *slice* a
  derived exception into its base type (Module 28).
- Order `catch` blocks from **most specific** to **most general**.

## Designing your own exception hierarchy

The standard library gives you a hierarchy rooted at `std::exception`:

```
std::exception
 ├── std::logic_error        (a bug: something that should never happen)
 │    ├── std::invalid_argument
 │    ├── std::out_of_range
 │    └── std::domain_error ...
 └── std::runtime_error      (a problem only detectable while running)
      ├── std::overflow_error
      └── ...
```

For a real application it pays to add **your own** hierarchy on top,
so that calling code can catch *exactly* the problems it knows how to
handle:

```cpp
class ClinicError : public std::runtime_error {      // root of OUR hierarchy
public:
    using std::runtime_error::runtime_error;          // inherit its constructor (Module 28)
};

class ValidationError : public ClinicError {         // bad data was supplied
public:
    using ClinicError::ClinicError;
};

class NotFoundError : public ClinicError {           // something looked up doesn't exist
public:
    using ClinicError::ClinicError;
};

class SafetyLimitError : public ClinicError {        // an action would be unsafe
public:
    using ClinicError::ClinicError;
};
```

Now different parts of the program can catch at the level they care
about:

```cpp
try {
    prescribe(patientId, drug, dose);
} catch (const SafetyLimitError& e) {    // very specific: ask a senior doctor
    escalate(e.what());
} catch (const ClinicError& e) {         // anything else from OUR code
    showMessage(e.what());
} catch (const std::exception& e) {      // anything at all (library, out of memory...)
    logAndAbort(e.what());
}
```

Guidelines:

- **Derive from a standard exception** (usually `std::runtime_error`
  or `std::logic_error`), so that a generic `catch (const
  std::exception&)` still catches yours and `what()` still works.
- **One root class per application or library** (`ClinicError`,
  `SchoolError`), so callers can catch "anything from this system".
- **Name exceptions after what went wrong**, not where:
  `InsufficientFundsError`, not `BankAccountError3`.
- Keep the hierarchy **small** — a handful of categories that callers
  will genuinely handle differently.

## Exceptions that carry information

Because exceptions are classes, they can carry **data** about what went
wrong — not just a message:

```cpp
class InsufficientFundsError : public BankError {
private:
    double requested;
    double available;
public:
    InsufficientFundsError(double req, double avail)
        : BankError("Insufficient funds: requested " + std::to_string(req) +
                    ", available " + std::to_string(avail)),
          requested(req), available(avail) {}

    double shortfall() const { return requested - available; }
};

// ...
} catch (const InsufficientFundsError& e) {
    std::cout << "You need GHS " << e.shortfall() << " more." << std::endl;
}
```

The catching code can now *do something useful* with the details,
instead of trying to parse a message string.

[`examples/01_exception_hierarchy.cpp`](examples/01_exception_hierarchy.cpp)
builds a small hierarchy with a data-carrying exception and catches at
different levels.

## When a constructor throws

Module 15 showed validating inside a constructor and throwing for bad
input. Here's precisely what happens:

```cpp
class Patient {
    std::string folder;
    VitalsLog log;          // a member object
    Thermometer probe;      // another member object
public:
    Patient(std::string f, int age) : folder(f), log(), probe("TH-1") {
        if (age < 0) throw ValidationError("age cannot be negative");
    }
    ~Patient();
};
```

- If a constructor throws, **the object never existed**. There's no
  half-built `Patient` to worry about — the code that tried to create
  it goes straight to a `catch`.
- **Its destructor does not run** (the object never finished being
  born).
- But every member and base class that **was** fully constructed
  before the throw **is destroyed** properly, in reverse order. Here,
  `probe`, `log` and `folder` are all destroyed.

That last point is the key: if every member manages its own resources
(RAII — `std::string`, `std::vector`, `std::unique_ptr`, ...), a
throwing constructor cleans up **automatically**. The danger is a
constructor that grabs a **raw** resource and then throws:

```cpp
class Recorder {
    double* buffer;
    std::ofstream file;
public:
    Recorder(int n, std::string filename) : buffer(new double[n]), file(filename) {
        if (!file) throw std::runtime_error("cannot open " + filename);  // LEAK!
    }
    ~Recorder() { delete[] buffer; }   // never runs - the object was never constructed
};
```

`buffer` is a raw pointer, which has no destructor of its own, so the
array leaks. The fix is the Rule of Zero again: make the member a
`std::vector<double>` or `std::unique_ptr<double[]>` (the array form
of `unique_ptr`, which calls `delete[]` for you; create one with
`std::make_unique<double[]>(n)`), and it will be cleaned up
automatically even when the constructor throws.

[`examples/02_constructor_throws.cpp`](examples/02_constructor_throws.cpp)
traces exactly which destructors run when a constructor throws.

## Destructors must not throw

During stack unwinding, C++ is already handling one exception. If a
destructor that runs during unwinding throws a **second** exception,
the program has two exceptions at once and no sensible way to continue,
so it calls `std::terminate()` — immediately ending the program.

To make this rule enforceable, **destructors are `noexcept` by
default**: if an exception escapes a destructor, `std::terminate()` is
called, whether or not another exception was in progress.

> **Rule:** a destructor must never let an exception escape. If the
> clean-up work can fail (closing a network connection, flushing a
> file), catch the exception **inside** the destructor and log or
> ignore it — or offer a separate `close()` method that *can* throw, so
> callers who care can call it first and handle the error themselves.

```cpp
class ConnectionGuard {
public:
    void close();                 // may throw - callers who care call this explicitly
    ~ConnectionGuard() {
        try {
            close();
        } catch (...) {           // "catch anything" - only acceptable in places like this
            // log it; never let it escape a destructor
        }
    }
};
```

[`examples/03_destructor_noexcept.cpp`](examples/03_destructor_noexcept.cpp)
shows this pattern.

## The exception-safety guarantees

When a member function throws part-way through, what state is the
object left in? There are three standard answers, called the
**exception-safety guarantees**. Every function you write gives one of
them (or, if badly written, none).

| Guarantee | Promise if an exception is thrown | Example |
|---|---|---|
| **No-throw** (`noexcept`) | It never throws at all. | Destructors, move operations (Module 25), `swap`, simple getters |
| **Strong** ("commit or roll back") | The operation either completes fully, or has **no effect at all** — the object is exactly as it was before. | `std::vector::push_back` (for most types) |
| **Basic** | Nothing leaks, and the object is still **valid** (its invariants hold) — but its contents may have changed. | Many operations that modify several things |
| *(none)* | Leaks, broken invariants, corrupted data. **Never acceptable.** | A function that frees memory before the replacement is allocated |

Aim for the **strong** guarantee where it's practical — it makes
errors much easier to reason about — and **never** go below basic.

### Getting the strong guarantee: do the risky work first

The simplest technique: **do everything that might throw on the side,
and only change the object's real state at the end, with operations
that can't throw.**

```cpp
// Transfer money between two accounts: must be all-or-nothing.
void Bank::transfer(const std::string& from, const std::string& to, Money amount) {
    Account& source = find(from);          // may throw NotFoundError - nothing changed yet
    Account& target = find(to);            // may throw NotFoundError - nothing changed yet
    if (source.balance() < amount) {
        throw InsufficientFundsError(...); // nothing changed yet
    }
    // From here on, nothing can throw: commit.
    source.debit(amount);
    target.credit(amount);
}
```

For a bigger change, work on a **copy** and **swap** it in at the end —
Module 24's copy-and-swap idea used for safety:

```cpp
void Timetable::replaceAll(const std::vector<std::string>& newSlots) {
    std::vector<Lesson> updated = lessons;     // work on a COPY (may throw - original untouched)
    for (const auto& s : newSlots) {
        updated.push_back(parseLesson(s));     // may throw - original still untouched
    }
    lessons.swap(updated);                     // commit: swap never throws
}
```

[`examples/04_strong_guarantee.cpp`](examples/04_strong_guarantee.cpp)
compares a version with no guarantee, a basic one, and a strong one,
each hit by the same failure part-way through.

## RAII + exceptions: why modern C++ code is safe

Look again at what stack unwinding does: it destroys every local object
in every function it leaves. Combine that with RAII (Module 23) and
smart pointers (Module 26), and **every resource is released
automatically on the exception path** — files closed, memory freed,
motors stopped, locks released — without a single `try`/`catch` written
for clean-up.

```cpp
void processBatch(const std::string& filename) {
    std::ifstream in(filename);                         // RAII: closes itself
    auto buffer = std::make_unique<double[]>(10000);   // RAII: frees itself
    MotorSession motor(conveyor);                       // RAII: stops itself
    for (...) {
        parseAndProcess(line);                          // may throw at any point
    }
}   // whether we leave normally or by exception, all three clean up
```

Compare that with raw `new`/`delete`, where *every* function that could
be interrupted by an exception needs a `try`/`catch` just to delete
things. [`examples/05_raii_vs_leak.cpp`](examples/05_raii_vs_leak.cpp)
shows the two side by side.

This is the real reason the course has pushed RAII, the Rule of Zero,
and smart pointers so hard: **they are what make exception-safe code
practical.**

## Rethrowing and translating exceptions

Sometimes a function wants to *react* to an exception — log it, add
context, clean up something non-RAII — but not *handle* it. Use
`throw;` (with no operand) inside a `catch` block to **rethrow the same
exception object**:

```cpp
try {
    loadRecords(file);
} catch (const std::exception& e) {
    std::cerr << "while loading " << file << ": " << e.what() << std::endl;
    throw;   // rethrow THE SAME exception - its real type is kept
}
```

Write `throw;`, not `throw e;` — `throw e;` throws a *copy* of `e`
**as the type you caught it as**, which slices a derived exception down
to `std::exception`.

At the boundary between two layers of a program it's often useful to
**translate** a low-level exception into one that makes sense at the
higher level:

```cpp
Patient Repository::load(const std::string& id) {
    try {
        return parsePatient(readLine(id));
    } catch (const std::invalid_argument& e) {                 // low-level: std::stod failed
        throw ValidationError("patient record " + id + " is corrupted: " + e.what());
    }
}
```

The caller now deals with a `ValidationError` from *our* hierarchy,
with useful context, instead of a puzzling `std::invalid_argument` from
deep inside a parsing function.

[`examples/06_rethrow_translate.cpp`](examples/06_rethrow_translate.cpp)
shows both.

## `noexcept` revisited

You met `noexcept` in Module 25 on move operations. In general:

- Mark a function `noexcept` when it **genuinely cannot throw** and
  callers benefit from knowing it: destructors (automatic), move
  constructors/assignment, `swap` functions, and simple getters.
- **Don't** add `noexcept` to functions that might throw. If an
  exception does escape a `noexcept` function, the program is
  terminated on the spot — `noexcept` is a promise, not a request.
- When in doubt, leave it off. The main places it matters are the ones
  listed above.

## Common beginner mistakes

- Catching exceptions by value (slicing) instead of by `const&`.
- Putting `catch (const std::exception&)` *before* more specific
  `catch` blocks — the specific ones then never run.
- Exception classes that don't derive from `std::exception`, so generic
  handlers miss them.
- Throwing from a destructor, or letting an exception escape one.
- A constructor that acquires a raw resource and then throws — leaking
  it, because the destructor never runs.
- Modifying an object *before* the step that might fail (losing the
  strong guarantee), e.g. freeing old data before allocating new.
- `throw e;` instead of `throw;` when rethrowing.
- Using exceptions for ordinary control flow ("not found" in a search
  that often finds nothing is often better as a `bool` or `nullptr`
  return — Module 15's guidance still applies).
- Catching an exception and silently ignoring it outside a destructor.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md), continuing your
   track.
4. Commit:

   ```bash
   git add 31-exceptions-in-class-design
   git commit -m "Complete Module 31: exceptions in class design"
   git push
   ```

Next: **[Module 32 — Templates Meet OOP](../32-templates-meet-oop/README.md)**.
