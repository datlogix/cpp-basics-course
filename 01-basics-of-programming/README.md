# Module 1 — Basics of Programming

## What is a program, really?

A computer only understands one language: electrical signals interpreted
as numbers — **machine code**. Nobody writes programs directly in machine
code anymore. Instead, we write in a **language humans can read** (like
C++), and a program called a **compiler** translates it into machine code
for us.

```
you write          compiler translates          computer runs
hello.cpp    --->      (g++)          --->        hello
(C++ source)                                   (machine code)
```

This is exactly what you did in Module 0 when you ran
`g++ hello.cpp -o hello`. Every C++ program you ever write follows this
same pipeline: **source code → compiler → executable → run**.

C++ is a **compiled language**. Contrast this with languages like Python,
which are **interpreted** — run line-by-line by another program every
time, with no separate "build" step. This is why compiled programs tend
to run faster (all the translation work happens once, ahead of time) but
have an extra step (you must recompile after every change).

## Anatomy of a C++ program

Look at the smallest complete C++ program:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, C++!" << std::endl;
    return 0;
}
```

Let's take it apart line by line.

### `#include <iostream>`

C++'s core language is small — even printing to the screen isn't built
in. Instead, functionality lives in **libraries** you pull in with
`#include`. `iostream` ("input/output stream") gives you `std::cout` (for
printing) and `std::cin` (for reading input, coming in Module 3). This
line must come before you use anything from that library.

### `int main() { ... }`

Every C++ program has exactly one `main` function — it's the **entry
point**: the first code that runs when your program starts. `int` means
main reports back a number when it finishes (see `return 0` below). The
`{` and `}` mark where main's body begins and ends — everything a
function does lives between its braces.

### `std::cout << "Hello, C++!" << std::endl;`

- `std::cout` — the "console output" stream, representing your terminal
  screen. `std::` says "this comes from the **std** (standard) library
  namespace" — a way of organizing names so different libraries don't
  clash. (In Module 0's setup you saw `using namespace std;` at the top of
  some files — that lets you write `cout` instead of `std::cout`
  everywhere below it. We write `std::` explicitly in this course so it's
  always clear where things come from, but you'll see both styles in real
  code.)
- `<<` — the "insertion operator": think of it as an arrow feeding data
  *into* the stream, i.e. onto the screen.
- `"Hello, C++!"` — a **string literal**: literal text, always in double
  quotes.
- `std::endl` — ends the current line (like pressing Enter), so the next
  output starts on a fresh line.
- `;` — a **semicolon** ends every statement in C++. Forget one and the
  compiler will complain — usually about the *next* line, which confuses
  beginners. If an error message makes no sense, check the line *above*
  it for a missing semicolon first.

### `return 0;`

Tells whoever ran the program "I finished successfully." `0` conventionally
means success; any other number signals some kind of error occurred. You
won't use this deliberately much yet, but it must be there in `main`.

## Statements, whitespace, and comments

- A **statement** is one instruction, ending in `;`. C++ doesn't care
  about line breaks or indentation the way Python does — they're purely
  for humans to read the code. *Always* indent consistently anyway; VS
  Code's C/C++ extension does this for you automatically.
- **Comments** are notes for humans that the compiler ignores entirely:

  ```cpp
  // A single-line comment — everything after // on this line is ignored.

  /* A multi-line comment.
     Everything between /* and */ is ignored, across as many lines as you like. */
  ```

  Use comments to explain *why* something is done a non-obvious way — not
  to restate what the code already says.

## Compiling and running — the two ways you'll use in this course

**Terminal (do this to really understand it):**

```bash
g++ myfile.cpp -o myfile
./myfile
```

**VS Code Code Runner (fast iteration once you're comfortable):** open
the `.cpp` file and click the ▶ button in the top-right corner, or press
`Ctrl+Alt+N`.

Both do the same thing. Use the terminal version whenever you want to be
sure you understand exactly what's happening — it's also what you'll use
on any computer that doesn't have VS Code.

## Errors are normal — read them, don't fear them

Try compiling this broken version (missing semicolon):

```cpp
#include <iostream>

int main() {
    std::cout << "Oops" << std::endl
    return 0;
}
```

`g++` will report something like:
`error: expected ';' before 'return'`

That's the compiler pointing almost exactly at the mistake. Reading
compiler errors is a skill — you'll get fast at it. The habit that
matters most right now: **fix the first error first, then recompile.**
One missing semicolon can produce five confusing-looking errors below it;
they usually all disappear once you fix the real one.

## Common beginner mistakes

- Forgetting the semicolon at the end of a statement.
- Mismatched `{` and `}` — VS Code highlights the matching brace when your
  cursor is next to one; use it.
- Forgetting `#include <iostream>` and then using `std::cout` — error
  will mention `cout` was not declared.
- Typos in `std::cout` (e.g. `Cout`, `cOut`) — C++ is **case-sensitive**.

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling and
   running each one.
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md).
4. Commit your work (see Module 0 §4.6 if you need a refresher):

   ```bash
   git add 01-basics-of-programming
   git commit -m "Complete Module 1: basics of programming"
   git push
   ```

Next: **[Module 2 — Data Types](../02-data-types/README.md)**.
