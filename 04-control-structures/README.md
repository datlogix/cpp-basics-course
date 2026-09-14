# Module 4 — Control Structures

Every program you've written so far runs top to bottom, once, no
decisions made. Control structures change that: they let a program
**decide** what to do (`if`) and **repeat** work (loops). This is the
module where programs stop feeling like a list of instructions and start
feeling *alive*.

## Comparison and logical operators (the building blocks)

Before `if` makes sense, you need expressions that evaluate to `bool`:

| Operator | Meaning | Example |
|----------|---------|---------|
| `==` | equal to | `age == 18` |
| `!=` | not equal to | `age != 18` |
| `<` `>` | less/greater than | `score > 50` |
| `<=` `>=` | less/greater or equal | `age >= 18` |
| `&&` | AND — both must be true | `age >= 18 && hasID` |
| `\|\|` | OR — at least one true | `isWeekend \|\| isHoliday` |
| `!` | NOT — flips true/false | `!isRaining` |

**The single most common beginner bug in this entire module:** confusing
`=` (assignment) with `==` (comparison).

```cpp
if (age = 18) { ... }   // BUG: assigns 18 to age, always true, wrong intent
if (age == 18) { ... }  // correct: compares age to 18
```

Modern compilers usually warn about this, but read every `if` you write
twice and check you meant `==`.

## `if`, `else if`, `else`

```cpp
int score = 72;

if (score >= 90) {
    std::cout << "Grade: A" << std::endl;
} else if (score >= 80) {
    std::cout << "Grade: B" << std::endl;
} else if (score >= 70) {
    std::cout << "Grade: C" << std::endl;
} else {
    std::cout << "Grade: F" << std::endl;
}
```

C++ checks conditions **top to bottom** and runs the **first** branch
that's true, then skips the rest entirely — order matters. If you
reordered these from smallest to largest, every score of 70+ would
incorrectly report "C" first. This is a real, easy-to-make bug — build
the habit of ordering range checks from most to least specific.

## `switch` — a clean alternative for exact matches

When you're comparing one variable against several *exact* values,
`switch` is often more readable than a long `if`/`else if` chain:

```cpp
char grade = 'B';

switch (grade) {
    case 'A':
        std::cout << "Excellent" << std::endl;
        break;
    case 'B':
        std::cout << "Good" << std::endl;
        break;
    case 'C':
        std::cout << "Average" << std::endl;
        break;
    default:
        std::cout << "Unknown grade" << std::endl;
}
```

`break` is not optional decoration — without it, execution **falls
through** into the next `case` regardless of whether it matches. This is
a real C++ footgun beginners hit constantly; always ask "did I put a
`break` at the end of every case?"

## Loops — repeating work

### `while` — repeat while a condition holds

```cpp
int count = 0;
while (count < 5) {
    std::cout << count << std::endl;
    count++;
}
```

Checks the condition **before** each run. If the condition starts false,
the body never runs at all.

### `do-while` — always runs at least once

```cpp
int choice;
do {
    std::cout << "Enter 1-3: ";
    std::cin >> choice;
} while (choice < 1 || choice > 3);
```

Use this specifically when you need the body to execute at least once
before the condition is even checked — the classic case is "ask for
input, validate it, ask again if it's bad."

### `for` — repeat a known number of times

```cpp
for (int i = 0; i < 5; i++) {
    std::cout << i << std::endl;
}
```

A `for` loop has three parts separated by `;`:
1. `int i = 0` — runs **once**, before the loop starts.
2. `i < 5` — checked **before every** iteration; loop stops when false.
3. `i++` — runs **after every** iteration's body finishes.

Use `for` when you know (or can compute) how many times to repeat. Use
`while` when you're repeating until some *condition* changes, and you
don't know in advance how many iterations that will take.

## Nested loops

Loops can contain other loops — essential for anything grid-like:

```cpp
for (int row = 1; row <= 3; row++) {
    for (int col = 1; col <= 3; col++) {
        std::cout << row * col << " ";
    }
    std::cout << std::endl;
}
```

The inner loop completes **all** of its iterations for every single
iteration of the outer loop.

## `break` and `continue`

- `break` — exit the loop immediately, skipping any remaining iterations.
- `continue` — skip the rest of *this* iteration's body, jump straight to
  the next one.

```cpp
for (int i = 1; i <= 10; i++) {
    if (i == 7) break;              // stop entirely once i is 7
    if (i % 2 == 0) continue;       // skip even numbers, don't print them
    std::cout << i << std::endl;    // prints 1, 3, 5
}
```

`%` is the **modulo** operator — it gives the *remainder* of division.
`i % 2 == 0` is the standard idiom for "is `i` even?" You'll use `%`
constantly from here on.

## Common beginner mistakes

- `if (x = 5)` instead of `if (x == 5)`.
- Forgetting `break` in a `switch`, causing fall-through.
- An infinite loop: forgetting to update the loop variable
  (`while (count < 5) { std::cout << count; }` — no `count++` — never
  stops. If your program seems frozen, this is almost always why; press
  `Ctrl+C` in the terminal to force-stop it).
- Off-by-one errors: `i <= 5` vs `i < 5` — always double-check whether
  the boundary should be inclusive.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — a number guessing
   game, **and** extend your Module 3 BMI calculator with real category
   detection.
4. Commit:

   ```bash
   git add 04-control-structures
   git commit -m "Complete Module 4: control structures"
   git push
   ```

Next: **[Module 5 — Data Structures](../05-data-structures/README.md)**.
