# Module 35 Project — A Test Suite for Your System

Continue your track. Each starter contains a small piece of your
system's core — a class with real rules, plus a service that depends on
an interface — and an empty test file. **The code was written without
tests, and contains exactly one bug.** Your tests should find it.

## Requirements (all tracks)

1. **Build setup.** `CMakeLists.txt` builds two programs from the same
   `src/` files: the real program and the **test** program (in `tests/`),
   and registers the tests with `ctest`. Build and run the tests with
   sanitizers:

   ```bash
   cmake -S . -B build -DCMAKE_CXX_FLAGS="-g -fsanitize=address,undefined"
   cmake --build build
   ctest --test-dir build --output-on-failure
   ```

   (or: `g++ -std=c++17 -Wall -Wextra -g -fsanitize=address,undefined -Iinclude src/<class files>.cpp tests/*.cpp -o tests_program` —
   leave out `src/main.cpp`, because the test file has its own `main`.)

2. **At least 25 checks** in `tests/`, using `minitest.h` and
   Arrange–Act–Assert, one behaviour per `testCase`, with descriptive
   names. Cover for every public method: normal cases, **boundaries**,
   invalid input, rule violations (exceptions), and **the object's state
   after a failure** (does it give the strong guarantee?).
3. **A fake.** Test the service class with a **fake** implementation of
   its interface that records calls (and, if useful, returns controlled
   values). No real output channel may be used in the tests.
4. **Find and fix the bug.** In `TESTING.md`, record which test found
   it, the failure message, how you located it (did you use `gdb`?),
   and the fix. Commit the failing test **first**, then the fix, as two
   separate commits.
5. **TDD a new feature** (listed per track), strictly red → green →
   refactor. Record each cycle in `TESTING.md` (test name, why it
   failed, what made it pass).
6. **Sanitizers.** Temporarily introduce one memory bug (e.g. use a
   deleted pointer, or index past the end of a raw array), show the
   sanitizer report in `TESTING.md`, then remove it.
7. **(Stretch) Catch2.** Port at least ten of your checks to Catch2,
   using `FetchContent` as in the module's example 08.

## Track A — Generic: Fee Accounts

- `FeeAccount` — charges, payments and balance for one student.
  Rules: charges and payments must be positive; a payment may not exceed
  the balance owed (paying *exactly* the balance must be allowed);
  every transaction is kept in a history.
- `FeeReminder` — given a list of accounts and a `Notifier&`, sends one
  reminder per account whose balance is **above** a threshold.
- **TDD feature:** `FeeAccount::applyBursary(double percent)` — reduces
  the *outstanding balance* by a percentage (0 < percent ≤ 100), and
  records it in the history.

## Track B — Electrical/Electronic Engineering: Circuit Loads

- `Circuit` — loads on one circuit with a breaker rating (in amps) at
  230 V. Rules: load names are unique; watts must be positive; adding a
  load that would push the total current **above** the rating is refused
  (exactly reaching the rating is allowed); `totalAmps()` is the sum of
  each load's `watts / 230`.
- `LoadMonitor` — checks a list of circuits and raises an `Alarm&` for
  each circuit running above 80% of its rating.
- **TDD feature:** `Circuit::shedLargestLoad()` — removes the load with
  the highest wattage and returns its name (throws on an empty circuit).

## Track C — Biomedical Engineering: Dose Calculation

- `DoseCalculator` — weight-based dosing (mg per kg) with a maximum
  single dose. Rules: weight must be greater than 0 and at most 300 kg;
  mg/kg must be positive; the dose is capped at the maximum single dose.
  *(Simplified for teaching — not for clinical use.)*
- `PrescriptionChecker` — checks a list of prescriptions against daily
  limits and pages the pharmacist (through a `Pager&`) for each one
  over its limit.
- **TDD feature:** `DoseCalculator::volumeMl(double doseMg, double
  concentrationMgPerMl)` — the volume to draw up, rounded to the nearest
  0.1 mL (throws if the concentration is not positive).

## Starter folders

- [`generic_starter/`](generic_starter/)
- [`ee_starter/`](ee_starter/)
- [`biomedical_starter/`](biomedical_starter/)

## When you're done

```bash
git add 35-testing-debugging
git commit -m "Complete Module 35 project: test suite, bug fix and TDD feature"
git push
```
