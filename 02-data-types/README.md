# Module 2 — Data Types

## Why types exist

A computer stores everything as bits (0s and 1s). Whether those bits mean
"the number 65", "the letter A", or "the price $65.00" depends entirely
on how the program agreed to interpret them. A **data type** is that
agreement: it tells the compiler *how much memory to reserve* and *how to
interpret the bits stored there*.

This matters immediately and practically: `5 / 2` gives a different
answer in C++ depending on the types involved, as you'll see below. Types
aren't bureaucracy — they change your program's actual behavior.

## The core built-in types

| Type | Stores | Example literal | Typical size |
|------|--------|------------------|--------------|
| `int` | Whole numbers | `42`, `-7` | 4 bytes |
| `double` | Decimal numbers (higher precision) | `3.14`, `-0.5` | 8 bytes |
| `float` | Decimal numbers (lower precision, less common) | `3.14f` | 4 bytes |
| `char` | A single character | `'A'`, `'7'`, `'$'` | 1 byte |
| `bool` | True or false | `true`, `false` | 1 byte |
| `std::string` | Text of any length | `"Hello"` | varies |

A few things worth noticing immediately:

- `char` literals use **single** quotes (`'A'`); `std::string`/text
  literals use **double** quotes (`"Hello"`). Mixing these up is a very
  common beginner error and the compiler error message for it is not
  always obvious.
- `std::string` is not a built-in language type like the others — it
  comes from the standard library, so using it requires:

  ```cpp
  #include <string>
  ```

  (In practice `<iostream>` often pulls this in transitively, but always
  `#include <string>` explicitly when you use `std::string` — never rely
  on an include "leaking in" from somewhere else.)

## Finding out a type's size yourself

```cpp
#include <iostream>

int main() {
    std::cout << "int: "    << sizeof(int)    << " bytes" << std::endl;
    std::cout << "double: " << sizeof(double) << " bytes" << std::endl;
    std::cout << "char: "   << sizeof(char)   << " bytes" << std::endl;
    std::cout << "bool: "   << sizeof(bool)   << " bytes" << std::endl;
    return 0;
}
```

`sizeof` isn't something you'll use daily, but seeing real numbers makes
"a type reserves memory" concrete instead of abstract.

## Type conversion (casting)

Mixing types often forces C++ to convert one to match the other —
**implicitly**, which can surprise you:

```cpp
int a = 7;
int b = 2;
std::cout << a / b << std::endl;        // prints 3, NOT 3.5!
```

Because both `a` and `b` are `int`, C++ performs **integer division**: it
computes the whole-number result and throws away the remainder. This
catches nearly every beginner at least once. To get a decimal answer, at
least one operand must be a floating-point type:

```cpp
double result = static_cast<double>(a) / b;   // 3.5
```

`static_cast<double>(a)` is **explicit casting**: you're telling the
compiler "convert this value to a `double` on purpose, right here." This
is the modern, preferred C++ style — you'll also see the older C-style
`(double)a` in existing code; both work, but prefer `static_cast` in code
you write.

## Booleans and comparisons (a preview)

You won't use `bool` heavily until Module 4, but it's worth meeting now:

```cpp
bool isRaining = true;
bool hasUmbrella = false;
std::cout << isRaining << std::endl;   // prints 1 (true prints as 1, false as 0)
```

## Common beginner mistakes

- Using single quotes for text (`'Hello'`) instead of double quotes
  (`"Hello"`) — single quotes are only for exactly one character.
- Expecting `int / int` to give a decimal result.
- Forgetting `#include <string>` when using `std::string`.
- Storing a decimal value in an `int` and being surprised it gets
  truncated (cut off, not rounded): `int x = 9.8;` silently stores `9`.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — a unit converter.
4. Commit:

   ```bash
   git add 02-data-types
   git commit -m "Complete Module 2: data types"
   git push
   ```

Next: **[Module 3 — Variables](../03-variables/README.md)**.
