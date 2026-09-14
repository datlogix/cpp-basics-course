# Module 3 — Variables

You've already been using variables since Module 2 without a formal
definition. Time to fill that gap properly.

## What a variable actually is

A **variable** is a named location in memory that holds a value of a
particular type. Declaring one has three parts:

```cpp
int age = 21;
// ^     ^   ^
// type  name  initial value
```

- **Declaration**: `int age;` — tells the compiler "reserve space for an
  `int` named `age`." Its value is **undefined/garbage** until you set
  it — never read a variable before giving it a value.
- **Initialization**: `age = 21;` — gives it a value.
- Combined, `int age = 21;`, is a **definition** — the form you should
  use almost always. Declaring without initializing is a common source of
  bugs for beginners (using a variable that technically "exists" but
  holds junk).

## Naming rules and conventions

**Rules (the compiler enforces these):**
- Must start with a letter or underscore, not a digit.
- Can contain letters, digits, underscores — no spaces, no `-`, no `!` etc.
- Cannot be a reserved keyword (`int`, `return`, `class`, etc.).
- Case-sensitive: `total` and `Total` are different variables.

**Conventions (the compiler doesn't care, but professionals do, and so
should you):**
- `camelCase` for variable names in C++: `totalPrice`, `firstName`,
  `isEnrolled`.
- Names should say *what the value represents*, not its type:
  `studentCount` is good; `intVar1` is not.
- Booleans read best as yes/no questions: `isActive`, `hasPermission`.

## Assignment vs. re-assignment

```cpp
int score = 0;      // initialization
score = 10;          // re-assignment: the type never changes, only the value
score = score + 5;   // reads current value (10), adds 5, stores 15 back
```

C++ gives you shorthand for that last, extremely common pattern:

```cpp
score += 5;   // same as score = score + 5;
score -= 2;   // same as score = score - 2;
score *= 3;   // same as score = score * 3;
score /= 2;   // same as score = score / 2;

score++;      // same as score = score + 1;  ("increment")
score--;      // same as score = score - 1;  ("decrement")
```

You'll see `++` constantly once loops arrive in Module 4 — get
comfortable with it now.

## Constants: values that must never change

```cpp
const double PI = 3.14159;
```

`const` tells the compiler "lock this value in — refuse to compile if
anything later tries to change it." This isn't just a style preference:
it's a safety net. If you accidentally write `PI = 4;` somewhere later in
a large program, the compiler catches it immediately instead of you
discovering a wrong answer during testing. Use `const` for any value that
represents a fixed fact (a tax rate, a maximum size, a physical constant)
by convention.

## Reading input: `std::cin`

Variables become far more interesting once a *user* can set their value,
not just you as the programmer:

```cpp
#include <iostream>

int main() {
    std::string name;
    std::cout << "What's your name? ";
    std::cin >> name;
    std::cout << "Hello, " << name << "!" << std::endl;
    return 0;
}
```

- `std::cin` is the input counterpart to `std::cout`.
- `>>` ("extraction operator") points *from* the stream *into* your
  variable — the mirror image of `<<`.
- `std::cin >> name` **pauses the program** until the user types
  something and presses Enter.

**Careful:** `std::cin >> someString` reads only a **single word** (it
stops at the first space). To read a whole line including spaces, use
`std::getline`:

```cpp
std::string fullName;
std::cout << "Full name: ";
std::getline(std::cin, fullName);
```

## Scope: where a variable "lives"

A variable declared inside `{ }` only exists inside those braces:

```cpp
int main() {
    int x = 5;
    {
        int y = 10;
        std::cout << x << std::endl;  // fine — x is visible here
    }
    std::cout << y << std::endl;      // ERROR — y no longer exists out here
    return 0;
}
```

This matters a lot once `if` blocks and loops arrive in Module 4 — a
variable declared inside a loop's `{ }` is recreated fresh every
iteration and doesn't exist outside it.

## Common beginner mistakes

- Using a variable before initializing it (reading garbage).
- Confusing `=` (assignment) with `==` (equality comparison — Module 4).
- Trying to reassign a `const` variable.
- Using `std::cin >> name` for input that contains spaces and being
  confused when only the first word comes through.
- Declaring a variable inside `{ }` and trying to use it outside.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — a BMI calculator that
   reads real user input.
4. Commit:

   ```bash
   git add 03-variables
   git commit -m "Complete Module 3: variables"
   git push
   ```

Next: **[Module 4 — Control Structures](../04-control-structures/README.md)**.
