# Module 3 Project — BMI Calculator

Build an interactive Body Mass Index (BMI) calculator. This is your first
program that actually *talks to its user*.

## Formula

```
BMI = weight (kg) / (height (m) * height (m))
```

## Requirements

1. Prompt the user and read their **weight in kilograms** (`double`)
   using `std::cin`.
2. Prompt the user and read their **height in meters** (`double`) — e.g.
   `1.75`.
3. Compute their BMI using the formula above and store it in a `double`.
4. Print the BMI clearly, e.g. `Your BMI is: 22.86`.
5. Declare the category boundaries as `const double` values (don't just
   use `18.5`, `25`, `30` directly in comparisons — name them):
   - `UNDERWEIGHT_MAX = 18.5`
   - `NORMAL_MAX = 25.0`
   - `OVERWEIGHT_MAX = 30.0`

You don't yet know `if` (that's Module 4), so for now just **print all
three constants alongside the computed BMI** so the user can compare
manually, e.g.:

```
Your BMI is: 22.86
(Underweight below 18.5, Normal up to 25, Overweight up to 30, Obese above)
```

> We'll come back to this exact project in Module 4 and add automatic
> category detection with `if`/`else if` — so keep this file, you'll
> extend it rather than start over.

## Starter file

Open [`starter.cpp`](starter.cpp).

## When you're done

```bash
g++ starter.cpp -o bmi
./bmi
```

```bash
git add 03-variables
git commit -m "Complete Module 3 project: BMI calculator"
git push
```
