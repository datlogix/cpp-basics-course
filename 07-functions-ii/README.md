# Module 7 — Functions II

Module 6 covered what a function *is*. This module covers four things
that make functions dramatically more powerful: **pass by reference**,
**default parameters**, **function overloading**, and **recursion**.

## Pass by reference — letting a function modify the caller's variable

Recall from Module 6: pass by value copies the argument, so changes
inside the function don't escape it. Sometimes you *want* a function to
modify the caller's actual variable — that's what a **reference
parameter** (`&`) is for:

```cpp
void doubleIt(int &x) {   // note the &
    x = x * 2;
}

int main() {
    int number = 5;
    doubleIt(number);
    std::cout << number << std::endl;  // 10 now! the function changed it directly
    return 0;
}
```

`int &x` means "`x` is not a copy — it's another name for whatever
variable the caller passed in." Anything you do to `x` happens directly
to `number`. This is exactly how you'll write a function that needs to
hand back *more than one* result (a `return` statement can only return
one value; reference parameters are the classic way around that):

```cpp
void minMax(std::vector<int> values, int &smallest, int &largest) {
    smallest = values[0];
    largest = values[0];
    for (int v : values) {
        if (v < smallest) smallest = v;
        if (v > largest) largest = v;
    }
}

int main() {
    std::vector<int> nums = {4, 9, 1, 7};
    int lo, hi;
    minMax(nums, lo, hi);
    std::cout << "min: " << lo << " max: " << hi << std::endl;
    return 0;
}
```

**Rule of thumb:** use pass by value (the default) unless you have a
specific reason to modify the caller's variable or hand back more than
one value — then use `&`.

## Default parameters

You can give a parameter a default value, used when the caller omits
that argument:

```cpp
void greet(std::string name, std::string greeting = "Hello") {
    std::cout << greeting << ", " << name << "!" << std::endl;
}

int main() {
    greet("Ama");                 // "Hello, Ama!"
    greet("Kofi", "Good morning"); // "Good morning, Kofi!"
    return 0;
}
```

Default parameters must come **last** in the parameter list — you can't
have a defaulted parameter followed by a non-defaulted one.

## Function overloading — same name, different parameters

C++ lets multiple functions share a name, as long as their **parameter
lists** differ (in number or type of parameters). The compiler picks the
right one based on what you pass:

```cpp
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

int main() {
    std::cout << add(2, 3) << std::endl;        // calls the int version -> 5
    std::cout << add(2.5, 3.1) << std::endl;     // calls the double version -> 5.6
    return 0;
}
```

This is why `std::cout << x` works no matter what type `x` is — behind
the scenes, `<<` is overloaded for every built-in type (and you can
overload operators for your own types too, though that's beyond this
course).

## Recursion — a function that calls itself

A **recursive** function solves a problem by solving a smaller version
of the *same* problem, until it reaches a version simple enough to
answer directly (the **base case**).

```cpp
int factorial(int n) {
    if (n <= 1) {          // base case: stops the recursion
        return 1;
    }
    return n * factorial(n - 1);  // recursive case: smaller version of the same problem
}
```

Trace `factorial(4)` by hand — this is the single best way to build
intuition for recursion:

```
factorial(4) = 4 * factorial(3)
             = 4 * (3 * factorial(2))
             = 4 * (3 * (2 * factorial(1)))
             = 4 * (3 * (2 * 1))
             = 24
```

Every recursive function needs **two things**, always:
1. A **base case** — a condition simple enough to answer without
   recursing further. Without one, the function calls itself forever
   (until the program crashes with a **stack overflow** — yes, that's
   where the website's name comes from).
2. A **recursive case** that moves *closer* to the base case each time
   (here, `n - 1` gets smaller every call, heading toward `n <= 1`).

### When to use recursion vs. a loop

Anything recursion can do, a loop can also do (and vice versa, for
finite problems) — Module 6's `factorial` used a loop. Recursion tends to
read more naturally for problems that are naturally defined in terms of
smaller versions of themselves (tree structures, some math sequences).
For simple counting/accumulating problems like `factorial`, a loop is
usually just as clear and slightly more efficient — recursion here is
primarily for building the *concept*, which you will need later for more
complex structures.

## Common beginner mistakes

- Forgetting `&` and being confused why the caller's variable didn't
  change (silently falls back to pass-by-value behavior — no error,
  just the wrong result).
- A recursive function with **no base case**, or a base case that's
  never actually reached — infinite recursion, crashes the program.
- Overloading two functions that only differ by **return type** (not
  allowed — overloads must differ in parameters).
- Putting a defaulted parameter before a non-defaulted one.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — recursive
   Fibonacci visualizer + a refactored Rock-Paper-Scissors game.
4. Commit:

   ```bash
   git add 07-functions-ii
   git commit -m "Complete Module 7: functions II"
   git push
   ```

Next: **[Module 8 — Classes and Objects](../08-classes-and-objects/README.md)**.
