# Module 6 Project — Math Toolkit

Build a small library of reusable math functions, then a `main` that
exercises all of them. The point isn't the math — it's practicing
designing clean function signatures (name, parameters, return type).

## Required functions

1. `double rectangleArea(double length, double width)`
2. `double circleArea(double radius)` (use `3.14159` for pi, or declare a
   `const double PI` above your functions and use that)
3. `double celsiusToFahrenheit(double celsius)` (reuse the Module 2
   formula, now as a real function instead of one-off code)
4. `int factorial(int n)` — for `n = 5`, computes `5 * 4 * 3 * 2 * 1 = 120`
   (a **loop-based** version is fine here; Module 7 revisits this
   recursively)
5. `bool isPrime(int n)` — returns whether `n` is a prime number

## Requirements

- Every function above needs a **prototype** before `main`, and its full
  definition can go below `main` — practice the pattern from the lesson.
- In `main`, call every function at least twice with different inputs,
  printing clearly labeled results.

## Starter file

Open [`starter.cpp`](starter.cpp) — prototypes are already stubbed in for
you; fill in the bodies below `main`.

## When you're done

```bash
g++ starter.cpp -o math_toolkit
./math_toolkit
```

```bash
git add 06-functions-i
git commit -m "Complete Module 6 project: math toolkit"
git push
```
