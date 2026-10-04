# Module 35 — Testing & Debugging OO Code

So far, you've checked your programs by **running them and reading
the output**. That works for a 50-line exercise. It doesn't work for a
system with twenty classes, where a change to `Gradebook` might quietly
break the report cards — and you'd only find out when a parent
complains.

Professional programmers protect their code with **automated tests**:
small programs that check the real program's classes, and can be re-run
in seconds after every change. When something does go wrong, they use
**debuggers** and **sanitizers** to find the cause quickly, instead of
scattering `std::cout` lines everywhere.

This module covers:

- **why** automated tests matter, and what a good test looks like
- `assert` — the simplest possible check
- **unit tests** and the **Arrange–Act–Assert** structure
- building a **tiny test framework** yourself, to see how real ones work
- **what to test** in a class: invariants, edge cases, exceptions,
  guarantees
- testing with **fakes**, made possible by dependency injection
  (Module 33)
- **test-driven development** (TDD): red, green, refactor
- a real framework: **Catch2**, with CMake and `ctest`
- **debugging** with `gdb` (and your editor's debugger)
- **sanitizers** that catch memory errors automatically
- stricter **compiler warnings**

## Why automated tests?

A test is code that **runs your code and checks the result**:

```cpp
BankAccount account("Ama", 100);
account.withdraw(30);
check(account.balance() == 70);   // if not, the test FAILS and says where
```

Tests pay off in four ways:

1. **Confidence to change code.** Refactoring (Module 33) is only safe
   if you can prove the behaviour didn't change. A test suite *is* that
   proof — re-run it after every step.
2. **Bugs found early**, minutes after you wrote them, while the code
   is still fresh in your mind — not weeks later.
3. **Documentation that can't go out of date.** A test like
   `withdrawing more than the balance throws InsufficientFundsError`
   tells the next programmer exactly how the class behaves.
4. **Better design.** Code that's hard to test is usually badly
   designed (too many responsibilities, hidden dependencies). Writing
   tests pushes you towards SOLID.

## `assert` — the simplest check

The `<cassert>` header provides `assert(condition)`. If the condition is
false, the program stops immediately and prints the file, line and
condition:

```cpp
#include <cassert>

double average(const std::vector<double>& v) {
    assert(!v.empty());     // a "this should never happen" check for programmers
    ...
}
```

```
program: example.cpp:7: double average(...): Assertion `!v.empty()' failed.
Aborted
```

`assert` is great for checking **assumptions inside your own code**.
But it has limits as a testing tool: it stops at the *first* failure,
it can't check that an exception is thrown, and asserts are switched
off entirely when a program is compiled with `-DNDEBUG` (common in
release builds). So for tests we want something a little better.

[`examples/01_assert_basics.cpp`](examples/01_assert_basics.cpp)

## Unit tests and Arrange–Act–Assert

A **unit test** checks one small piece of behaviour of one unit
(usually one class or function), in isolation. Good unit tests have a
consistent three-part shape:

```cpp
// Test: withdrawing reduces the balance
// ARRANGE - set up the objects you need
BankAccount account("Ama", 100);
// ACT - do the one thing being tested
account.withdraw(30);
// ASSERT - check the result
CHECK(account.balance() == 70);
```

Guidelines:

- **One behaviour per test**, with a name that describes it:
  `withdrawing more than the balance is refused`, not `test3`.
- **Independent**: each test creates its own objects. Tests must pass
  in any order.
- **Fast and repeatable**: no keyboard input, no real network, no
  real SMS — same result every run.
- **Test behaviour, not implementation**: check what the public
  interface promises, not private details. Then you can refactor the
  inside freely without rewriting tests.

## A tiny test framework, by hand

Real projects use a framework (below), but writing a small one first
shows you there's no magic. Our `minitest.h` (in `examples/`) provides
three checks:

```cpp
CHECK(condition);                       // passes if condition is true
CHECK_EQ(actual, expected);             // passes if they're equal; prints both if not
CHECK_THROWS(statement, ExceptionType); // passes if the statement throws that type
```

…and a `TEST_SUMMARY()` that prints how many checks passed and failed,
and returns a non-zero exit code if anything failed (so scripts and
build tools can tell).

They're written as **macros** — `#define`d by the preprocessor, the
same tool that handles `#include` and `#pragma once` (Module 22). A
macro can do something a normal function can't: capture the **text**
of the condition and the **line number** where it was written, so a
failure message can say exactly which check failed:

```
FAIL test_bank_account.cpp:31: CHECK_EQ(account.balance(), 70) - got 100, expected 70
```

Read [`examples/minitest.h`](examples/minitest.h) — it's about 40
lines. Then [`examples/02_first_unit_tests.cpp`](examples/02_first_unit_tests.cpp)
uses it to test a `BankAccount`.

> In normal code, prefer functions, `const` variables and templates
> over macros — macros ignore namespaces and scopes, and can surprise
> you. Test frameworks are one of the few places where they earn their
> keep.

## What to test in a class

For each public method, think about:

| Kind of test | Example (for `BankAccount::withdraw`) |
|---|---|
| **Normal case** | withdraw 30 from 100 leaves 70 |
| **Boundaries** | withdraw exactly the whole balance; withdraw 0.01 |
| **Invalid input** | withdraw 0, withdraw −5 → throws `std::invalid_argument` |
| **Rule violations** | withdraw 150 from 100 → throws `InsufficientFundsError` |
| **State after failure** (Module 31) | after a refused withdrawal, the balance is **unchanged** (strong guarantee) |
| **Invariants** | the balance is never negative, whatever sequence of calls |
| **Interaction** | transfer moves money: one balance down, the other up, total unchanged |

And for the class as a whole:

- **Constructors**: valid arguments create a correct object; invalid
  ones throw (Module 31).
- **Copying and moving** (Modules 24–25): a copy is independent; a
  moved-from object is valid.
- **Polymorphism** (Module 29): each derived class honours the base
  class's promises (Module 33's LSP) — the same tests should pass for
  every subclass.

[`examples/03_testing_exceptions.cpp`](examples/03_testing_exceptions.cpp)
tests exceptions and the strong guarantee.

## Testing with fakes

How do you test `FeeReminderService` (Module 33) without sending real
text messages to real parents? How do you test an overheat alarm
without heating a real sensor?

Thanks to **dependency injection**, you can pass the class a **fake**
version of its dependency — one that implements the same interface but
just **records** what happened, or returns **controlled** values:

```cpp
class FakeSender : public MessageSender {
public:
    std::vector<std::string> sent;                          // records every call
    void send(const std::string& to, const std::string& text) override {
        sent.push_back(to + ": " + text);
    }
};

// ARRANGE
FakeSender fake;
FeeReminderService service(fake);
// ACT
service.remind({{"0244000001", 350}, {"0244000002", 0}});
// ASSERT
CHECK(fake.sent.size() == 1);    // only the parent who owes money was messaged
```

Fakes that return controlled values (a `FakeThermometer` that reports
exactly 39.5 °C) let you test behaviour that's hard to trigger for real.
You'll also hear the words **stub** (returns canned answers) and
**mock** (also checks it was called correctly); the idea is the same.

This is the payoff of Module 33's Dependency Inversion Principle:
**code that depends on interfaces can be tested in isolation.** A class
that creates its own `BulkSmsGateway` inside can't be.

[`examples/04_fake_dependency.cpp`](examples/04_fake_dependency.cpp)

## Test-driven development (TDD)

**TDD** turns the usual order around: write the test **first**.

1. **Red** — write a small test for behaviour that doesn't exist yet.
   Run it and watch it **fail** (that proves the test can fail).
2. **Green** — write the **simplest** code that makes it pass.
3. **Refactor** — tidy the code (and the tests), re-running the tests
   to make sure they stay green.

Repeat, one small behaviour at a time.

Why bother? Writing the test first forces you to decide **how the class
will be used** before you write it — which usually produces a cleaner
interface. And you never end up with untested code, because no code is
written without a failing test asking for it.

[`examples/05_tdd_walkthrough.cpp`](examples/05_tdd_walkthrough.cpp)
shows the final code of a TDD session, with comments recording each
red–green–refactor cycle.

## A real framework: Catch2

Real projects use an established framework. Two popular ones for C++
are **Catch2** and **GoogleTest**; they're very similar. Catch2 tests
look like this:

```cpp
#include <catch2/catch_test_macros.hpp>
#include "fraction.h"

TEST_CASE("fractions are stored in lowest terms") {
    Fraction f(2, 4);
    REQUIRE(f.numerator() == 1);       // REQUIRE stops this test case if it fails
    CHECK(f.denominator() == 2);       // CHECK records the failure and carries on
}

TEST_CASE("division by a zero denominator is rejected") {
    REQUIRE_THROWS_AS(Fraction(1, 0), std::invalid_argument);
}

TEST_CASE("adding fractions") {
    Fraction half(1, 2);

    SECTION("adding a third") {         // each SECTION runs with a fresh `half`
        CHECK(half + Fraction(1, 3) == Fraction(5, 6));
    }
    SECTION("adding a negative") {
        CHECK(half + Fraction(-1, 2) == Fraction(0, 1));
    }
}
```

The easiest way to use it is to let **CMake download it** with
`FetchContent`:

```cmake
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.7.1
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests tests/test_fraction.cpp src/fraction.cpp)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)   # provides main() for you

enable_testing()
add_test(NAME fraction_tests COMMAND tests)
```

```bash
cmake -S . -B build          # the first run downloads Catch2 (needs internet)
cmake --build build
./build/tests                # run directly...
ctest --test-dir build       # ...or through CMake's test runner
```

[`examples/08_catch2_project/`](examples/08_catch2_project/) is a
complete, ready-to-build Catch2 project.

> **No internet?** Everything in this module's exercises and project
> works with `minitest.h` alone. Use Catch2 when you can.

## Debugging with `gdb`

When a test fails (or the program crashes) and the reason isn't
obvious, a **debugger** lets you pause the program, step through it
line by line, and look at variables — far faster than adding and
removing `std::cout` lines.

First, compile with debugging information (`-g`) and without
optimisation:

```bash
g++ -std=c++17 -Wall -Wextra -g -O0 07_debugger_demo.cpp -o demo
gdb ./demo
```

The commands you'll use most:

| Command | Short | What it does |
|---|---|---|
| `break average` / `break demo.cpp:25` | `b` | pause when that function or line is reached |
| `run` | `r` | start the program |
| `next` | `n` | run the current line, stepping *over* function calls |
| `step` | `s` | run the current line, stepping *into* function calls |
| `print total` / `print scores.size()` | `p` | show a variable or expression |
| `info locals` | | show all local variables |
| `backtrace` | `bt` | show the chain of function calls that led here — essential after a crash |
| `continue` | `c` | run until the next breakpoint |
| `watch balance` | | pause whenever this variable changes |
| `quit` | `q` | exit |

A typical session for a crash: `run`, the program stops at the crash,
`backtrace` to see where you are and how you got there, `print` the
suspicious variables, then `break` earlier and `run` again to watch
them go wrong.

**Graphical debuggers** do exactly the same things with buttons: in VS
Code, install the C/C++ extension, set a breakpoint by clicking left of
a line number, and press F5. (On macOS, the debugger is `lldb`; its
commands are almost identical.)

[`examples/07_debugger_demo.cpp`](examples/07_debugger_demo.cpp)
contains a deliberate bug, with a step-by-step `gdb` walkthrough in its
comments.

## Sanitizers: let the compiler find memory bugs

Some of the worst C++ bugs — using freed memory, reading past the end
of an array, double `delete`, leaks — often **don't crash** straight
away. The program just behaves strangely, sometimes, on some machines.

GCC and Clang can build **sanitizers** into your program: extra checks
that detect these bugs **the moment they happen**, and print exactly
where:

```bash
g++ -std=c++17 -g -fsanitize=address,undefined 06_sanitizer_demo.cpp -o demo
./demo
```

- **AddressSanitizer** (`address`) catches use-after-free,
  out-of-bounds access, double delete, and (on Linux) **memory leaks**.
- **UndefinedBehaviorSanitizer** (`undefined`) catches things like
  signed integer overflow and invalid casts.

A report looks like this (shortened):

```
ERROR: AddressSanitizer: heap-use-after-free on address 0x502000000010
READ of size 8 at 0x502000000010 thread T0
    #0 in Sensor::read() const 06_sanitizer_demo.cpp:22
    #1 in useAfterFree() 06_sanitizer_demo.cpp:28
    #2 in main 06_sanitizer_demo.cpp:53
freed by thread T0 here:
    #0 in operator delete(void*, unsigned long)
    #1 in useAfterFree() 06_sanitizer_demo.cpp:27
```

Read it top to bottom: *what* went wrong, *where* it was used, and
*where* the memory was freed. You've had the option of
`-fsanitize=address` since Module 24's exercise; from now on, **build
and run your tests with sanitizers on** as a habit.

(Sanitizers are available with GCC/Clang on Linux and macOS, and
partly on Windows via MSVC or Clang. On Windows with MinGW, run them
under WSL.)

[`examples/06_sanitizer_demo.cpp`](examples/06_sanitizer_demo.cpp)
contains three deliberate memory bugs, each switched on by a
command-line argument.

## Stricter warnings

Since Module 20 you've compiled with `-Wall -Wextra`. A few more flags
catch further mistakes:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -Wconversion file.cpp
```

- `-Wpedantic` — warns about non-standard extensions.
- `-Wshadow` — warns when a variable hides another with the same name
  (e.g. a constructor parameter `name` hiding the member `name`).
- `-Wconversion` — warns about conversions that might lose information
  (`double` → `int`).

In team projects, **`-Werror`** turns every warning into an error, so
the build simply can't succeed with warnings in it.

## Putting it together: a testing workflow

1. Keep tests in their own file(s) — e.g. `tests/test_gradebook.cpp` —
   built as a **separate executable** from the real program, sharing
   the same `src/*.cpp` files.
2. Build tests with `-g -fsanitize=address,undefined`.
3. Run the tests after **every** change. Commit only when they pass.
4. When you find a bug, **first write a test that reproduces it** (it
   fails), then fix the bug (it passes). The bug can never silently
   return.

## Common beginner mistakes

- Tests that depend on each other or on the order they run in.
- Tests that only check the "happy path" — no boundaries, errors, or
  exceptions.
- Testing private implementation details, so every refactor breaks the
  tests.
- Using real files, keyboards, networks or clocks in unit tests — use
  fakes.
- Classes that create their own dependencies, making fakes impossible
  (go back to Module 33's DIP).
- Ignoring a failing test "because it's probably the test that's
  wrong" — find out which is wrong.
- Debugging an optimised build without `-g` — variables show as
  "optimized out" and lines jump around.
- Turning sanitizers off because they "make the program crash" — they're
  showing you a real bug that was already there.

## Try it yourself

1. Work through [`examples/`](examples/). Build each test example with
   `-fsanitize=address,undefined`.
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md): a test suite for
   your track.
4. Commit:

   ```bash
   git add 35-testing-debugging
   git commit -m "Complete Module 35: testing and debugging OO code"
   git push
   ```

Next: **[Module 36 — Capstone Project 3](../36-capstone-project-3/README.md)**.
