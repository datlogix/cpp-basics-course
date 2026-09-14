# Module 4 Project — Number Guessing Game (+ revisit the BMI Calculator)

## Part A: Number Guessing Game

Build the classic "guess the number" game:

1. Pick a secret number and store it in an `int` (hard-code it for now,
   e.g. `42` — `<cstdlib>` random numbers are a nice stretch goal below,
   not a requirement).
2. Use a loop (`while` or `do-while`) that:
   - Prompts the user to guess.
   - Reads their guess.
   - If too high, prints `"Too high!"`.
   - If too low, prints `"Too low!"`.
   - If correct, prints `"You got it!"` and **stops the loop**.
3. Track and print the number of guesses it took once they win.

### Stretch goal: a real random secret number

```cpp
#include <cstdlib>  // for rand(), srand()
#include <ctime>    // for time()

srand(static_cast<unsigned int>(time(0)));  // seed once, at the very top of main
int secret = rand() % 100 + 1;              // random number from 1 to 100
```

## Part B: Revisit the BMI Calculator

Open your Module 3 `03-variables/project/starter.cpp` BMI calculator.
Copy it into this module's `project/bmi_v2.cpp` and add real category
detection using `if`/`else if`/`else` against the `const double`
boundaries you already declared, printing exactly one category, e.g.:

```
Your BMI is: 22.86
Category: Normal
```

This is the payoff of learning control structures: the same project
becomes noticeably smarter with no new data, just decision-making added
on top.

## Starter files

- [`starter.cpp`](starter.cpp) — Part A.
- [`bmi_v2.cpp`](bmi_v2.cpp) — Part B.

## When you're done

```bash
g++ starter.cpp -o guessing_game && ./guessing_game
g++ bmi_v2.cpp -o bmi_v2 && ./bmi_v2
```

```bash
git add 04-control-structures
git commit -m "Complete Module 4 project: guessing game + BMI v2"
git push
```
