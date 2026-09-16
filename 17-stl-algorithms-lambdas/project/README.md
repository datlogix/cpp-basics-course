# Module 17 Project — A Signal/Series Analyzer

Pick **one** track. All three take a raw series of readings and apply
`sort`, `max_element`/`min_element`, `transform`, and `count_if` to
analyze it — the same shape as the exercise, applied at project scale.

## Track A — Generic: Exam Score Analyzer

1. Read `n` exam scores from the user into a `vector<double>`.
2. Print the sorted list, the highest and lowest score.
3. Using `transform` and a lambda, convert every raw score (out of a
   given max, e.g. `80`) to a percentage (`score / maxScore * 100.0`).
4. Using `count_if`, count how many students scored below `50%`.

## Track B — Electrical/Electronic Engineering: Waveform Analyzer

1. Read `n` raw ADC sample values (integers, `0`–`1023`) from the user
   into a `vector<int>`.
2. Using `transform` and a lambda, convert every raw sample to a voltage
   in the range `0.0`–`5.0` V (`raw / 1023.0 * 5.0`).
3. Print the sorted voltages, and the peak (`max_element`) and lowest
   (`min_element`) voltage.
4. Using `count_if` and a captured threshold constant, count how many
   samples represent an **over-voltage event** (e.g. above `4.5` V).

## Track C — Biomedical Engineering: Vital Sign Analyzer

1. Read `n` raw heart-rate sensor readings from the user into a
   `vector<double>`.
2. Print the sorted readings, and the highest and lowest.
3. Using `count_if` and captured threshold constants, count how many
   readings are **abnormal** (outside `60`–`100` bpm).
4. Using `transform` and a lambda, build a "risk score" for every
   reading: `abs(reading - 80.0)` (distance from a healthy resting
   average of `80`) — then find the reading with the **highest** risk
   score using `max_element` on the risk-score vector.

## Starter files

- [`generic_starter.cpp`](generic_starter.cpp)
- [`ee_starter.cpp`](ee_starter.cpp)
- [`biomedical_starter.cpp`](biomedical_starter.cpp)

## When you're done

```bash
g++ <your_chosen_starter>.cpp -o analyzer_project
./analyzer_project
```

```bash
git add 17-stl-algorithms-lambdas
git commit -m "Complete Module 17 project: signal/series analyzer"
git push
```
