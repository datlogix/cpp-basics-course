# Module 15 Project — A Safety-Checked Calculator

Pick **one** track. All three build a small interactive calculator that
validates input with exceptions instead of trusting it blindly, and
keeps running after a bad entry instead of crashing.

## Track A — Generic: Safe Grade Averager

1. Loop, reading scores from the user one at a time (`0`–`100`) until
   they type a sentinel value (e.g. `-1`) to stop.
2. Throw `std::invalid_argument` (and catch it, printing a clear message
   and re-prompting) for any score outside `0`–`100`.
3. After the loop, print the average of all *valid* scores entered.

## Track B — Electrical/Electronic Engineering: Circuit Safety Checker

1. Loop, reading a voltage and a resistance from the user for an Ohm's
   Law calculation (`current = voltage / resistance`).
2. Throw `std::invalid_argument` if resistance is `<= 0` (an
   unrealistic/unsafe circuit value).
3. Catch it, print a clear error, and let the user try again rather than
   crashing.
4. Also compute the resulting current and, if it exceeds a
   `const double MAX_SAFE_CURRENT` (e.g. `5.0` amps), throw and catch a
   **second** kind of exception (`std::runtime_error`) with a message
   like `"Overcurrent condition!"`.
5. Loop until the user types a sentinel value to stop, then print how
   many calculations succeeded vs. how many were rejected.

## Track C — Biomedical Engineering: Dosage Safety Checker

1. Build the `Dosage` class from Module 13/14 (or a simpler version)
   whose constructor throws `std::invalid_argument` for a negative
   value.
2. Loop, reading a patient weight (kg) and a per-kg dosage rate
   (mg/kg) from the user, computing `totalDose = weight * ratePerKg`.
3. Throw a `std::runtime_error` if `totalDose` exceeds a
   `const double MAX_SAFE_DOSE_MG` (e.g. `500.0`), with a clear message.
4. Catch both exception types (most-specific first), printing a clear
   message and letting the user try another patient rather than
   crashing.
5. Loop until the user types a sentinel value to stop, then print how
   many dosage calculations succeeded vs. were rejected as unsafe.

## Starter files

- [`generic_starter.cpp`](generic_starter.cpp)
- [`ee_starter.cpp`](ee_starter.cpp)
- [`biomedical_starter.cpp`](biomedical_starter.cpp)

## When you're done

```bash
g++ <your_chosen_starter>.cpp -o safety_project
./safety_project
```

```bash
git add 15-exception-handling
git commit -m "Complete Module 15 project: safety-checked calculator"
git push
```
