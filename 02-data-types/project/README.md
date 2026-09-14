# Module 2 Project — Temperature Converter

Build a program that converts a **hard-coded** temperature from Celsius
to Fahrenheit and Kelvin, printing all three clearly. (We hard-code the
input for now — reading real user input arrives in Module 3. This project
is entirely about picking the *right types* and getting the *math*
right.)

## Formulas

- `Fahrenheit = Celsius * 9.0 / 5.0 + 32.0`
- `Kelvin = Celsius + 273.15`

## Requirements

1. Store the starting Celsius temperature in a `double` (pick any value,
   e.g. `25.0`).
2. Compute Fahrenheit and Kelvin into their own `double` variables using
   the formulas above.
3. Print all three values with clear labels, e.g.:

   ```
   25 C = 77 F = 298.15 K
   ```

4. **Deliberately break it once, on purpose**: change the Celsius
   variable to an `int` instead of `double`, recompile, and see whether
   the output changes. Add a one-line comment in your code explaining
   what you observed and why (this is where the "integer division
   surprise" from the lesson shows up in a project you built yourself).
   Then change it back to `double` before you commit.

## Starter file

Open [`starter.cpp`](starter.cpp).

## When you're done

```bash
g++ starter.cpp -o converter
./converter
```

```bash
git add 02-data-types
git commit -m "Complete Module 2 project: temperature converter"
git push
```
