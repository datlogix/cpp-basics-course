# Module 17 — STL Algorithms & Lambdas

You've hand-written loops for nearly every task so far: finding a
maximum, counting matches, transforming values. The STL's `<algorithm>`
header provides ready-made, well-tested versions of these extremely
common patterns — and **lambdas** let you plug in your own custom logic
without writing a separate named function every time. Together, they let
you write *what* you want done instead of *how* to loop to do it.

## `std::sort`

```cpp
#include <algorithm>
#include <vector>

std::vector<int> scores = {77, 92, 85, 60};
std::sort(scores.begin(), scores.end());
// scores is now {60, 77, 85, 92}
```

Every STL algorithm takes a **range**, expressed as two iterators (see
Module 16): "start here" (`.begin()`) and "stop just before here"
(`.end()`). This same begin/end pattern is used by essentially every
algorithm in this header — learn it once, apply it everywhere.

## `std::max_element` / `std::min_element`

```cpp
#include <algorithm>

auto peakIt = std::max_element(scores.begin(), scores.end());
std::cout << "Peak: " << *peakIt << std::endl;
```

These return an **iterator** pointing at the largest/smallest element,
not the value itself — dereference it with `*` to get the actual value,
exactly as with any iterator.

## `std::find`

```cpp
auto it = std::find(scores.begin(), scores.end(), 85);
if (it != scores.end()) {
    std::cout << "Found 85!" << std::endl;
} else {
    std::cout << "Not found." << std::endl;
}
```

`std::find` returns `.end()` specifically to signal "not found" — the
exact same idiom as `nullptr` (Module 10) and `map::find` (Module 16):
a special sentinel value meaning "nothing here," always checked before
you trust the result.

## Lambdas — a function written inline, on the spot

A **lambda** is a small, unnamed function you define exactly where you
need it:

```cpp
auto isPassing = [](int score) {
    return score >= 50;
};

std::cout << isPassing(72) << std::endl;  // 1 (true)
```

- `[]` — the **capture list** (more on this below).
- `(int score)` — parameters, exactly like a normal function.
- `{ return score >= 50; }` — the body, exactly like a normal function.
- `auto isPassing = ...` — you can store a lambda in a variable and call
  it like any function, but its real power is being passed *directly*
  into an algorithm, with no separate name needed at all.

## `std::count_if` — count matches using a lambda

```cpp
#include <algorithm>

int numPassing = std::count_if(scores.begin(), scores.end(),
    [](int score) { return score >= 50; });

std::cout << "Passing: " << numPassing << std::endl;
```

The lambda is passed as the **predicate** — a function returning
`true`/`false` for each element, used to decide whether it counts. This
single line replaces a hand-written loop with an `if` and a counter
variable — genuinely more direct once the pattern feels natural.

## `std::transform` — build a new sequence from an old one

```cpp
#include <algorithm>

std::vector<int> rawAdcCounts = {0, 512, 1023};
std::vector<double> voltages(rawAdcCounts.size());  // pre-sized destination

std::transform(rawAdcCounts.begin(), rawAdcCounts.end(), voltages.begin(),
    [](int raw) { return raw / 1023.0 * 5.0; });   // convert to 0-5V range
```

`std::transform` applies your lambda to every element of the source
range and writes each result into the destination range (which must
already have enough room — hence `voltages(rawAdcCounts.size())` above,
sizing it upfront rather than growing it with `push_back`).

## Capturing variables from the surrounding scope

A lambda can use variables from outside itself by **capturing** them in
the `[ ]`:

```cpp
double threshold = 4.5;

int numOverThreshold = std::count_if(voltages.begin(), voltages.end(),
    [threshold](double v) { return v > threshold; });   // capture by value
```

- `[threshold]` — capture `threshold` **by value** (a copy, read-only
  inside the lambda).
- `[&threshold]` — capture **by reference** (changes inside the lambda
  affect the original — rarely needed for the read-only patterns in
  this course).
- `[=]` — capture everything used, by value; `[&]` — capture everything
  used, by reference. Convenient, but naming exactly what you capture
  (as above) is clearer and safer, and is what this course prefers.

## Putting it together

```cpp
std::vector<double> voltages = {2.1, 4.8, 3.3, 5.0, 1.9};
const double THRESHOLD = 4.5;

std::sort(voltages.begin(), voltages.end());

auto peak = std::max_element(voltages.begin(), voltages.end());
std::cout << "Peak voltage: " << *peak << std::endl;

int overCount = std::count_if(voltages.begin(), voltages.end(),
    [THRESHOLD](double v) { return v > THRESHOLD; });
std::cout << "Over-voltage events: " << overCount << std::endl;
```

## Common beginner mistakes

- Forgetting `#include <algorithm>`.
- Forgetting that `max_element`/`find` return an **iterator**, not the
  value — dereference with `*` before using it, and check against
  `.end()` before dereferencing at all.
- Sizing the destination of `std::transform` incorrectly — it writes
  into existing elements; it doesn't `push_back` for you.
- Capturing more than you actually need with `[=]`/`[&]` out of habit —
  prefer naming exactly what a lambda captures.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — pick the Generic,
   EE, or Biomedical track.
4. Commit:

   ```bash
   git add 17-stl-algorithms-lambdas
   git commit -m "Complete Module 17: STL algorithms and lambdas"
   git push
   ```

Next: **[Module 18 — Templates](../18-templates/README.md)**.
