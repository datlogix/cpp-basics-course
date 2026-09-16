# Module 10 Project — Dynamic Buffer

Pick **one** of the three tracks below. All three practice exactly the
same core skill — allocate a runtime-sized array with `new[]`, fill it,
compute statistics, free it with `delete[]` — applied to a different
domain. Pick whichever is most relevant to you, or do more than one.

## Track A — Generic: Dynamic Grade Book

Build a program that:

1. Reads an integer `n` — the number of students.
2. Dynamically allocates a `double[n]` for their scores.
3. Reads `n` scores from the user into the array.
4. Computes and prints the minimum, maximum, and average score.
5. Frees the array with `delete[]` and sets the pointer to `nullptr`.

## Track B — Electrical/Electronic Engineering: ADC Sample Buffer

Simulate a data-acquisition buffer for an analog-to-digital converter
(ADC):

1. Read an integer `n` — the number of samples to capture.
2. Dynamically allocate a `double[n]` buffer.
3. Read `n` raw sample values from the user (imagine these are voltage
   readings from a sensor, e.g. `0.0`–`5.0` V).
4. Compute and print: minimum voltage, maximum voltage (the **peak**),
   and average voltage.
5. **Stretch goal:** flag any sample above `4.5` V as an "over-voltage
   event" and count how many occurred.
6. Free the buffer with `delete[]`.

## Track C — Biomedical Engineering: Vital Sign Buffer

Simulate a patient monitoring buffer for a single vital sign (e.g. heart
rate in beats per minute):

1. Read an integer `n` — the number of readings taken during a
   monitoring session.
2. Dynamically allocate a `double[n]` buffer.
3. Read `n` heart-rate readings from the user.
4. Compute and print: minimum, maximum, and average heart rate over the
   session.
5. **Stretch goal:** flag any reading outside a safe resting range (e.g.
   below `60` or above `100` bpm) as "abnormal" and count how many
   occurred.
6. Free the buffer with `delete[]`.

## Starter files

- [`generic_starter.cpp`](generic_starter.cpp)
- [`ee_starter.cpp`](ee_starter.cpp)
- [`biomedical_starter.cpp`](biomedical_starter.cpp)

## When you're done

```bash
g++ <your_chosen_starter>.cpp -o buffer_project
./buffer_project
```

```bash
git add 10-pointers-dynamic-memory
git commit -m "Complete Module 10 project: dynamic buffer"
git push
```
