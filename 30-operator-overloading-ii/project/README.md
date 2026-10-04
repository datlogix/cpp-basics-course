# Module 30 Project — A Value Type That Feels Built-In

Continue your track. Every track needs one **value type** — a small
class that represents a quantity — that should be as natural to use as
a `double`. You'll give it a complete, well-chosen set of operators,
plus a container class with `[]` and a functor for use with STL
algorithms.

All three starters build with **C++20** (for `<=>`):

```bash
cmake -S . -B build && cmake --build build && ./build/<program>
# or: g++ -std=c++20 -Wall -Wextra -Iinclude src/*.cpp -o program
```

## Requirements (all tracks)

1. **Compound assignment members** (`+=`, `-=`, and the others your
   type needs) returning `*this` by reference.
2. **Binary operators as non-members** built on the compound ones,
   including the **symmetric** forms your track lists (e.g. both
   `x * 3` and `3 * x`).
3. **`<<` and `>>` as friends.** `>>` must leave the object unchanged
   and fail the stream on bad input. Test it with an
   `std::istringstream`.
4. **Comparisons** — with `<=>`/`==`, *or* a written explanation of why
   your type should **not** be ordered (one track has to make this
   call).
5. **A container class with `operator[]`** in both `const` and
   non-`const` versions, with bounds or key checking.
6. **A functor** with state, used with at least one STL algorithm
   (`count_if`, `transform`, `sort`, ...). In a comment, write the
   equivalent lambda.
7. **A judgement table.** In a comment at the top of your value type's
   header, list every operator you *considered* and say whether you
   provided it and why. At least two must be **rejected** with a good
   reason.

## Track A — Generic: School Fees in Ghana Cedis

- **Value type:** `Money`, stored as a whole number of **pesewas**
  (`long`) to avoid rounding errors. `+`, `-`, `+=`, `-=`, `Money * int`
  and `int * Money` (e.g. fees × number of terms), `Money / int`
  (splitting a bill — what happens to the leftover pesewas? Decide and
  document it), unary `-`, `<<` printing `GHS 1,250.50`, `>>` reading
  `1250.50`, and `<=>`.
- **Container:** `FeeLedger`, mapping student IDs to their outstanding
  balance: `Money& operator[](const std::string& studentId)` (creating
  a zero balance for a new ID) and a `const` version that throws
  `std::out_of_range` for an unknown ID.
- **Functor:** `OwesMoreThan` (holds a `Money` threshold) — count the
  students owing more than GHS 500.

## Track B — Electrical/Electronic Engineering: Complex Impedance

- **Value type:** `Impedance`, a complex number `R + jX` in ohms
  (resistance + reactance). `+` (series), `-`, `*`, `/` (complex
  arithmetic), `+=`, `-=`, `*=`, `/=`, `Impedance * double` and
  `double * Impedance`, `<<` printing `100 + j37.7 ohm` (or `- j` for
  negative reactance), `>>` reading the form `100 37.7` (R then X),
  `magnitude()` and `phaseDegrees()`.
- **Parallel combination:** add a free function
  `Impedance parallel(const Impedance& a, const Impedance& b)` using
  `(a * b) / (a + b)`.
- **Ordering:** complex numbers have **no natural order**. Do *not*
  provide `<=>`; provide `==` only, and explain why in your judgement
  table. Then write a named functor `ByMagnitude` to sort impedances
  when you need to.
- **Container:** `Network`, holding components by designator
  (`"R1"`, `"L1"`, `"C1"`): `operator[]` in both versions, throwing for
  unknown designators in the `const` one.
- **Functor:** `ImpedanceAt` (holds a frequency in Hz) that turns a
  component description (type + value) into an `Impedance`, used with
  `std::transform`.

## Track C — Biomedical Engineering: Medication Doses

- **Value type:** `Dose`, stored as a whole number of **micrograms**
  (`long`). `+`, `-`, `+=`, `-=`, `Dose * int` and `int * Dose` (doses
  per day), `<<` printing `500 mg` or `250 mcg` (whichever is clearer),
  `>>` reading `500 mg` or `250 mcg` (rejecting other units), and
  `<=>`.
- **Rejected on purpose:** `Dose * Dose` and `Dose / Dose` are
  meaningless — reject them in your judgement table. (What *would*
  `Dose / double` mean? Decide.)
- **Container:** `MedicationChart`, one patient's scheduled doses for
  each hour of the day: `Dose& operator[](int hour)` and a `const`
  version, both throwing `std::out_of_range` outside `0..23`.
- **Functor:** `ExceedsLimit` (holds a maximum single `Dose`) — count
  the hours whose scheduled dose is above the limit, and add a check
  that the **total** daily dose is below a daily maximum.

## Starter folders

- [`generic_starter/`](generic_starter/)
- [`ee_starter/`](ee_starter/)
- [`biomedical_starter/`](biomedical_starter/)

## When you're done

```bash
git add 30-operator-overloading-ii
git commit -m "Complete Module 30 project: a complete value type"
git push
```
