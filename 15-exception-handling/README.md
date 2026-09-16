# Module 15 — Exception Handling

Every program in this course so far has assumed the "happy path": the
user types a valid number, the file exists, the calculation makes
sense. Real programs constantly meet situations that break that
assumption — invalid input, a missing file, a calculation that doesn't
make physical sense. **Exception handling** is C++'s structured way of
detecting these situations and responding deliberately, instead of
crashing or silently producing a wrong answer.

## The problem, without exceptions

```cpp
double computeOhmsLawCurrent(double voltage, double resistance) {
    return voltage / resistance;   // what if resistance is 0?
}
```

If `resistance` is `0`, this doesn't necessarily crash — dividing a
`double` by `0.0` produces a special value (`inf`), which then silently
propagates through every later calculation that uses it, corrupting
results far from where the real problem occurred. Bugs like this are
some of the hardest to track down precisely *because* nothing visibly
went wrong at the moment of the mistake.

## `throw` — signal that something is wrong

```cpp
#include <stdexcept>

double computeOhmsLawCurrent(double voltage, double resistance) {
    if (resistance <= 0) {
        throw std::invalid_argument("Resistance must be positive.");
    }
    return voltage / resistance;
}
```

`throw` immediately stops normal execution and starts searching for
code prepared to handle this specific kind of problem — it does **not**
return a value or continue to the next line. `std::invalid_argument` is
one of several standard **exception types** from `<stdexcept>`, each
naming a different broad category of problem (there's also
`std::out_of_range`, `std::runtime_error`, and others).

## `try` / `catch` — respond to the problem

```cpp
try {
    double current = computeOhmsLawCurrent(12.0, 0.0);
    std::cout << "Current: " << current << std::endl;
} catch (const std::invalid_argument& e) {
    std::cout << "Error: " << e.what() << std::endl;
}
```

- `try { ... }` — wraps code that *might* throw.
- `catch (const std::invalid_argument& e) { ... }` — runs *only* if a
  matching exception was thrown inside the `try` block. `e.what()`
  returns the message text passed to `throw`.
- If nothing throws, the `catch` block is simply skipped — exceptions
  add no overhead to the normal, successful path.
- Code after the `try`/`catch` continues running normally either way —
  the program has **recovered**, rather than crashing.

## Multiple `catch` blocks

You can catch different exception types differently, most-specific
first:

```cpp
try {
    // ... code that might throw different kinds of problems ...
} catch (const std::invalid_argument& e) {
    std::cout << "Invalid argument: " << e.what() << std::endl;
} catch (const std::out_of_range& e) {
    std::cout << "Out of range: " << e.what() << std::endl;
} catch (const std::exception& e) {
    std::cout << "Some other standard exception: " << e.what() << std::endl;
}
```

`std::exception` is the base class every standard exception type
derives from (this is exactly the inheritance from Module 11, and the
catch works polymorphically exactly as Module 12 described) — a final
`catch (const std::exception& e)` acts as a safety net for anything you
didn't specifically anticipate.

## Where exceptions actually come from in code you already use

You've already been near exceptions without necessarily noticing:
- `std::vector::at(index)` throws `std::out_of_range` for a bad index
  (unlike `operator[]`, which doesn't check and is undefined behavior
  instead — prefer `.at()` when you want the safety).
- `std::stod`/`std::stoi` (Module 14) throw `std::invalid_argument` if
  the text isn't a valid number.

```cpp
std::vector<int> scores = {90, 85, 77};
try {
    std::cout << scores.at(10) << std::endl; // out of bounds
} catch (const std::out_of_range& e) {
    std::cout << "Bad index: " << e.what() << std::endl;
}
```

## Writing your own exception-safe validation

A common, practical pattern: validate input at the boundary (where it
enters your program — user input, a file, a function argument) and
throw immediately if it's invalid, rather than letting a bad value drift
deep into your program's logic:

```cpp
class Dosage {
private:
    double milligrams;
public:
    Dosage(double mg) {
        if (mg < 0) {
            throw std::invalid_argument("Dosage cannot be negative.");
        }
        milligrams = mg;
    }
};
```

Now it's **impossible** to construct an invalid `Dosage` object at all —
the check happens exactly once, in exactly one place, and every part of
the program that uses `Dosage` can simply trust it's valid. This is
encapsulation (Module 8) and exception handling working together.

## When to use exceptions vs. a simple `if`

Exceptions are for **exceptional, unexpected** situations — bad input, a
missing file, a violated precondition. They are not a general substitute
for `if`/`else` control flow (Module 4) for routine, expected branching
(e.g. don't `throw` just to decide between two normal, everyday cases).
A rough rule: if the calling code is expected to routinely check for and
handle a condition as part of normal operation, prefer a return value or
`if`; if the condition represents something genuinely going wrong that
most callers won't anticipate at every call site, an exception is often
clearer.

## Common beginner mistakes

- Catching `std::exception` (or worse, `...` to catch literally
  anything) as the *only* handler, hiding which specific problem
  actually occurred.
- Forgetting `#include <stdexcept>`.
- Using `operator[]` instead of `.at()` when you actually want bounds
  checking — `[]` silently does nothing to protect you.
- Throwing exceptions for routine, expected conditions instead of using
  normal `if`/`else` — reserve exceptions for genuinely exceptional
  situations.
- Catching an exception and then doing nothing with it (an empty
  `catch` block) — this silently hides real problems; at minimum, log
  or print what happened.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — pick the Generic,
   EE, or Biomedical track.
4. Commit:

   ```bash
   git add 15-exception-handling
   git commit -m "Complete Module 15: exception handling"
   git push
   ```

Next: **[Module 16 — STL: Containers & Iterators](../16-stl-containers/README.md)**.
