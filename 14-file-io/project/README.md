# Module 14 Project — A Persistent Log

Pick **one** track. All three build a program that writes timestamped
(or session-tagged) records to a CSV file, appending across runs, then
reads the whole file back to compute a summary.

## Track A — Generic: Expense Log

1. Each run, prompt for a category (e.g. "Food") and an amount, and
   append `"<category>,<amount>"` to `expenses.csv`.
2. Read the whole file back, printing every entry.
3. Compute and print the **total** spent across all entries.

## Track B — Electrical/Electronic Engineering: Sensor Data Logger

1. Each run, prompt for a timestamp label (e.g. `"08:00"`) and a voltage
   reading, and append `"<timestamp>,<voltage>"` to `sensor_log.csv`.
2. Read the whole file back, printing every entry as
   `"<timestamp> -> <voltage> V"`.
3. Compute and print the **minimum, maximum, and average** voltage
   across every entry ever logged (not just this run — the whole file).

## Track C — Biomedical Engineering: Patient Vitals Log

1. Each run, prompt for a patient ID and a heart-rate reading, and
   append `"<patientId>,<heartRate>"` to `vitals_log.csv`.
2. Read the whole file back, printing every entry as
   `"Patient <patientId>: <heartRate> bpm"`.
3. Compute and print how many logged readings across the whole file fall
   **outside** the normal resting range (`60`–`100` bpm).

## Starter files

- [`generic_starter.cpp`](generic_starter.cpp)
- [`ee_starter.cpp`](ee_starter.cpp)
- [`biomedical_starter.cpp`](biomedical_starter.cpp)

## When you're done

Run your program **2–3 times** with different input to see the log
genuinely accumulate across runs — that's the entire point of this
module.

```bash
g++ <your_chosen_starter>.cpp -o log_project
./log_project
./log_project
./log_project
```

```bash
git add 14-file-io
git commit -m "Complete Module 14 project: persistent log"
git push
```

> Note: the `.csv` files your program creates while testing are your own
> generated data, not course material — feel free to delete them before
> committing, or leave them (either is fine; they won't affect grading).
