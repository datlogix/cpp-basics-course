# Module 32 Project — A Reusable Template Toolkit

Continue your track. You'll build a small **header-only toolkit** of
generic classes for your system — the kind of reusable code that ends
up in a team's shared library — and use it from your track's own
classes.

All three starters build with **C++20** (for concepts).

## Requirements (all tracks)

Put every template in `include/` (headers only — explain in a comment
in one header *why* template code can't go in a `.cpp` file).

1. **A class template with out-of-class member definitions** —
   `Statistics<T>` (count, mean, min, max, standard deviation), with
   every member function defined *below* the class in the header.
2. **A concept** constraining it: `Statistics` only accepts numeric
   types (`std::integral` or `std::floating_point`). Leave a commented
   line showing the error for a non-numeric type.
3. **A specialisation** for one type where the general recipe is wrong
   (described per track) — and a comment explaining why the
   specialisation's interface differs.
4. **A non-type template parameter** — a fixed-capacity
   `RollingWindow<T, N>` that keeps only the last `N` values, with a
   **member function template** `template <typename F> void
   forEach(F f) const`.
5. **A class template derived from an abstract base**, so that several
   instantiations can live in one `std::vector<std::unique_ptr<Base>>`
   and be handled with one loop.
6. **A second concept** describing *your own* track classes (below),
   and a function template constrained by it.
7. **Static vs dynamic.** In a comment at the top of `main.cpp`, say
   which parts of your program use static polymorphism and which use
   dynamic polymorphism, and justify each choice in one sentence.

## Track A — Generic: Reusable School Toolkit

- **Specialisation:** `Statistics<bool>` for attendance (present /
  absent) — "mean" makes no sense; give it `attendanceRate()` instead.
- **`RollingWindow<double, 5>`:** a student's last five test scores, for
  a "recent form" average.
- **Template + abstract base:** `ReportColumn<T> : public Column` — a
  report-card table whose columns hold different types (`std::string`
  names, `double` averages, `bool` "passed"), printed by one loop over
  `std::vector<std::unique_ptr<Column>>`.
- **Your concept:** `Gradable` — has `getName()` and `average()`; write
  `template <Gradable G> void printRanking(std::vector<G> people)`
  that sorts by average and prints a ranking. Use it with your
  `Student` class *and* a separate `Team` class (a robotics team's
  average score) that shares no base class with `Student`.

## Track B — Electrical/Electronic Engineering: Data-Logger Toolkit

- **Specialisation:** `Statistics<bool>` for switch/relay states — give
  it `dutyCycle()` (fraction of samples that were ON) instead of
  `mean()`.
- **`RollingWindow<double, 10>`:** the last ten voltage samples, for a
  moving-average filter.
- **Template + abstract base:** `LogChannel<T> : public Channel` — a
  data logger whose channels record different types (`double` volts,
  `int` pulse counts, `bool` relay states), all summarised by one loop
  over `std::vector<std::unique_ptr<Channel>>`.
- **Your concept:** `Readable` — has `read()` returning something
  convertible to `double`, and `unit()`; write `template <Readable S>
  void sampleInto(const S& sensor, Statistics<double>& stats, int n)`
  and use it with two sensor classes that share no base class.

## Track C — Biomedical Engineering: Clinical Data Toolkit

- **Specialisation:** `Statistics<bool>` for alarm states — give it
  `fractionInAlarm()` instead of `mean()`.
- **`RollingWindow<int, 6>`:** the last six heart-rate readings (one
  per 10 minutes = the last hour), for spotting a trend.
- **Template + abstract base:** `ChartColumn<T> : public Column` — an
  observation chart whose columns hold different types (`int` heart
  rate, `double` temperature, `bool` on-oxygen), printed by one loop
  over `std::vector<std::unique_ptr<Column>>`.
- **Your concept:** `HasVitalReading` — has `latestValue()` convertible
  to `double`, and `vitalName()`; write `template <HasVitalReading M>
  void trend(const M& monitor, ...)` and use it with two monitor classes
  that share no base class.

## Starter folders

- [`generic_starter/`](generic_starter/)
- [`ee_starter/`](ee_starter/)
- [`biomedical_starter/`](biomedical_starter/)

## When you're done

```bash
git add 32-templates-meet-oop
git commit -m "Complete Module 32 project: reusable template toolkit"
git push
```
