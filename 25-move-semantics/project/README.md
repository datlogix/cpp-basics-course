# Module 25 Project — Moving Big Data Instead of Copying It

Continue your track. Module 24's data class can now be copied safely —
but every copy duplicates the whole array. In this project you'll add
**move operations**, then *measure* how many expensive copies they
eliminate in a realistic workflow.

Each starter contains Module 24's class with a correct Rule of Three
already in place, plus two static counters (`copies` and `moves`) so
the program can report exactly what happened.

## Requirements (all tracks)

**Part 1 — Rule of Five.**

1. Add a **move constructor** and **move assignment operator**, both
   `noexcept`, both leaving the source *empty but valid*, both
   incrementing the `moves` counter.
2. Run the workflow in `main.cpp` and record the copy/move counts
   **before** and **after** your change in a table in a comment at the
   top of `main.cpp`.
3. Show, with output, that a moved-from object is still *valid*: print
   it (it should report 0 values without crashing), then assign it a
   new value and print it again.
4. Confirm there are no memory errors:

   ```bash
   g++ -std=c++17 -Wall -Wextra -fsanitize=address -Iinclude src/*.cpp -o program
   ./program
   ```

**Part 2 — Move-only.** Your RAII class from Module 23 is currently
non-copyable (Module 24). Make it **move-only**: keep copying deleted,
but add `noexcept` move operations so that the responsibility (an open
session, a running pump, a switched-on supply) can be **handed over**
— for example, returned from a function or stored in a
`std::vector`. The moved-from object's destructor must **not** release
the resource a second time. Prove it with tracing output.

**Part 3 — Reflect.** Answer in a comment: *"Which of my workflow's
copies were genuinely needed, and which were only happening because the
class couldn't move?"*

**Stretch.** Time the workflow with `<chrono>`:

```cpp
#include <chrono>
auto start = std::chrono::steady_clock::now();
// ... workflow ...
auto end = std::chrono::steady_clock::now();
std::cout << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";
```

and report the time before and after adding the move operations. Use a
large data size (e.g. 100,000 values) so the difference is visible.

## Track A — Generic: Building a Term Archive

`ScoreSheet` holds a form's scores for one subject. The workflow builds
a whole term's archive: a function `ScoreSheet loadSheet(...)` creates
and returns each sheet by value; `main` stores 60 sheets in a
`std::vector<ScoreSheet>` (6 forms × 10 subjects), and finally moves the
official sheet for "JHS 3 Science" out of the archive into a separate
`ScoreSheet` for moderation, using `std::move`.

## Track B — Electrical/Electronic Engineering: A Signal-Processing Pipeline

`Waveform` holds samples. The workflow is a pipeline of functions that
each **take a `Waveform` by value, modify it, and return it**:
`capture()` → `removeDcOffset(Waveform)` → `clip(Waveform, max)` →
`scale(Waveform, gain)`. Pass each stage's result into the next with
`std::move` (or directly as a temporary), and store 50 processed
captures in a `std::vector<Waveform>`.

## Track C — Biomedical Engineering: Handing Over ECG Recordings

`EcgTrace` holds an ECG recording. The workflow simulates 40 bedside
monitors each producing a recording (`EcgTrace recordBeat(...)`
returning by value) that is **handed over** to a central
`std::vector<EcgTrace>` archive with `std::move`. Finally, one
recording is moved out of the archive into a "referral" trace for a
cardiologist — and the program must show the archive slot it came from
is now empty but valid.

## Starter folders

- [`generic_starter/`](generic_starter/)
- [`ee_starter/`](ee_starter/)
- [`biomedical_starter/`](biomedical_starter/)

## When you're done

```bash
git add 25-move-semantics
git commit -m "Complete Module 25 project: move semantics and the Rule of Five"
git push
```
