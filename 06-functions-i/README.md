# Module 6 — Functions I

## Why functions exist

Look back at the Module 5 project: you probably computed "average of a
list of numbers" for multiple students, copying similar code each time.
Functions let you write that logic **once**, give it a name, and reuse it
anywhere. This is one of the most important ideas in all of programming:
**don't repeat yourself (DRY)**. If you ever copy-paste code and change
one small thing, that's almost always a sign you need a function instead.

You've actually been *calling* functions since Module 1 —
`std::cout <<` uses operator overloading (Module 7) internally, and
`scores.size()` and `scores.push_back(x)` are functions that belong to
`vector`. Now you'll write your own.

## Anatomy of a function

```cpp
int add(int a, int b) {
    int sum = a + b;
    return sum;
}
```

- `int` (first) — the **return type**: what kind of value this function
  hands back. Use `void` if it doesn't return anything (see below).
- `add` — the function's **name**. Same naming conventions as variables
  (`camelCase`), but should read like a verb/action: `add`, `calculateTax`,
  `printReceipt`.
- `(int a, int b)` — the **parameters**: named placeholders for the
  values the caller must provide, each with its own type.
- `{ ... }` — the **body**: what the function actually does.
- `return sum;` — hands a value back to whoever called this function,
  and immediately exits the function (any code after `return` in the
  same path never runs).

## Calling a function

```cpp
int main() {
    int result = add(3, 4);          // "arguments" 3 and 4 fill "parameters" a and b
    std::cout << result << std::endl; // 7
    return 0;
}
```

**Parameters vs. arguments** — a small but real distinction: *parameters*
are the named placeholders in the function's definition (`a`, `b`);
*arguments* are the actual values you pass when calling it (`3`, `4`).

## `void` functions — when there's nothing to return

Not every function computes a value; some just *do* something (print,
modify something, etc.):

```cpp
void printGreeting(std::string name) {
    std::cout << "Hello, " << name << "!" << std::endl;
    // no return statement needed - or you can write a bare `return;` to exit early
}
```

## Declaration order matters (and function prototypes)

C++ reads your file top to bottom. A function must be **declared before
it's used** — either by defining it earlier in the file, or by writing a
**prototype** (the signature only, ending in `;`) before `main`, with the
full definition afterward:

```cpp
#include <iostream>

double square(double x);  // prototype - tells the compiler this exists

int main() {
    std::cout << square(5.0) << std::endl;  // works: compiler already knows about square
    return 0;
}

double square(double x) {  // full definition, can come after main
    return x * x;
}
```

Prototypes matter more once you split code across files (a topic beyond
this course), but the underlying rule — *declared before used* — applies
inside a single file too. This is exactly why `main`, by convention, is
usually placed either first (with prototypes above it) or last (with
every other function defined above it) — never in the middle.

## Pass by value (the default, and what it really means)

```cpp
void tryToDouble(int x) {
    x = x * 2;
}

int main() {
    int number = 5;
    tryToDouble(number);
    std::cout << number << std::endl;  // still 5! not 10.
    return 0;
}
```

This surprises every beginner once. By default, C++ **copies** the
argument into the parameter. `x` inside `tryToDouble` is a completely
separate variable from `number` in `main` — changing `x` never touches
`number`. This is called **pass by value**. It's a deliberate safety
feature: a function can't accidentally corrupt the caller's data unless
you explicitly ask it to. (Module 7 introduces **pass by reference**,
which does let a function modify the caller's variable, on purpose.)

## Scope, revisited: parameters and local variables

Parameters and any variable declared inside a function body only exist
**inside that function** — exactly the `{ }` scope rule from Module 3.
`x` and `sum` in `add` above don't exist anywhere in `main`.

## Common beginner mistakes

- Forgetting `return` in a non-`void` function (compiler error, or
  undefined behavior in some cases).
- Mismatched return type: declaring `int` but returning a `double`
  silently truncates it.
- Calling a function before it's declared or defined anywhere above it.
- Expecting a pass-by-value parameter change to affect the caller's
  variable.
- Confusing the *order* of arguments with the *order* of parameters —
  `subtract(a, b)` and `subtract(b, a)` are not the same call.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — a Math Toolkit.
4. Commit:

   ```bash
   git add 06-functions-i
   git commit -m "Complete Module 6: functions I"
   git push
   ```

Next: **[Module 7 — Functions II](../07-functions-ii/README.md)**.
