# Module 24 Project — Safe Copies for "What-If" Analysis

Continue your track. In every track there's a good reason to **copy**
a large set of data: you want to experiment on a copy while keeping
the original untouched. You'll build the class two ways — once by
hand with the Rule of Three, and once with the Rule of Zero — and
compare them.

## Requirements (all tracks)

**Part 1 — Rule of Three, by hand.** Your track's data class
deliberately stores its values in a raw heap array (`new double[n]` or
`new int[n]`) so that you practise doing this properly once.

1. Write the **copy constructor** (deep copy) and **copy assignment
   operator** (self-assignment check, copy-then-free, `return *this`).
   The destructor is provided.
2. Add tracing output to all three (`[copy]`, `[assign]`, `[free]`) so
   the program's output proves when each runs.
3. Run the scenario in `main.cpp` (uncomment it once your functions
   exist). It must show the original is **unchanged** after the copy is
   modified.
4. Build once with `-fsanitize=address` added and confirm there are no
   errors:

   ```bash
   g++ -std=c++17 -Wall -Wextra -fsanitize=address -Iinclude src/*.cpp -o program
   ./program
   ```

**Part 2 — Non-copyable RAII.** Copy your RAII class from Module 23
into this project (`include/` and `src/`, and add it to
`CMakeLists.txt`). Make it **non-copyable** with `= delete`. In a
comment, show the line that would now fail to compile, and explain why
copying it would have been a bug.

**Part 3 — Rule of Zero.** Write a second version of your data class in
`include/<name>_v2.h` (header only is fine for this one) that stores its
values in a `std::vector` and declares **no** destructor, copy
constructor, or copy assignment. Run the same scenario with it. Then
answer in a comment at the top of `main.cpp`: *"How many lines of code
did the Rule of Zero version save, and which bugs is it immune to?"*

## Track A — Generic: Moderation "What-If" for Exam Scores

Class `ScoreSheet` stores the scores of one class (form) for one
subject in a `double*` array. Moderators want to see the effect of
adding bonus marks **without touching the official scores**:

- copy the official sheet, call `addBonus(5)` on the copy (capped at
  100), and print both averages and both pass rates (score ≥ 50);
- then use **copy assignment** to "reset" the experimental copy back to
  the official one and print it again.

## Track B — Electrical/Electronic Engineering: Waveform Processing

Class `Waveform` stores voltage samples of one cycle of a sine wave
(e.g. 230 V RMS mains at 50 Hz → peak ≈ 325 V) in a `double*` array.
Engineers want to try signal processing on a copy:

- copy the waveform, call `clip(maxVolts)` on the copy (any sample
  above `+max` or below `-max` is limited to it — simulating an
  overloaded amplifier), and print the RMS voltage of both
  (`RMS = sqrt(mean of the squares of the samples)`);
- then use **copy assignment** to restore the copy and print its RMS
  again.

## Track C — Biomedical Engineering: ECG Trace Annotation

Class `EcgTrace` stores an ECG recording as `int` samples in
microvolts, in an `int*` array. The **original recording is a medical
record and must never be altered**; clinicians work on a copy:

- copy the trace, call `smooth()` on the copy (replace each inner
  sample with the average of itself and its two neighbours — a simple
  moving-average filter), and print the peak (max) value of both;
- then use **copy assignment** to restore the working copy from the
  original and print its peak again.

## Starter folders

- [`generic_starter/`](generic_starter/)
- [`ee_starter/`](ee_starter/)
- [`biomedical_starter/`](biomedical_starter/)

## When you're done

```bash
git add 24-copy-semantics
git commit -m "Complete Module 24 project: Rule of Three vs Rule of Zero"
git push
```
