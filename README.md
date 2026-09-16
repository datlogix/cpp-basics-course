# Introduction to C++ Programming — A Beginner's Course

Welcome! This course takes you from **never having written a line of code** to
**building a multi-file C++ project with classes, functions, and data
structures, tracked in Git and pushed to GitHub.** No prior programming
experience is assumed.

## How this course is built

Every module follows the same shape, so you always know what to expect:

1. **`README.md`** — the lesson. Concepts explained in plain language, with
   the *why* before the *how*, plus common beginner mistakes.
2. **`examples/`** — small, runnable `.cpp` files that demonstrate exactly
   one idea at a time. Compile and run every single one yourself. Reading
   code you didn't type teaches you far less than watching your own build
   succeed (or fail) at the terminal.
3. **`exercises/`** — practice problems with starter files containing
   `TODO` markers. A `solutions/` folder sits next to them — try for at
   least 15 minutes before you look.
4. **`project/`** — a small, fun program that only uses what you've learned
   *so far*. This is the payoff for the module — something you'd actually
   want to show a friend.

## Roadmap

### Part 1 — Foundations

| # | Module | You will be able to... |
|---|--------|------------------------|
| 0 | [Setup: Tools, Git & GitHub](00-setup/README.md) | Install a compiler, use VS Code, and push code to GitHub |
| 1 | [Basics of Programming](01-basics-of-programming/README.md) | Explain how a C++ program becomes a running program, and write/compile your first one |
| 2 | [Data Types](02-data-types/README.md) | Choose the right type to store a piece of information |
| 3 | [Variables](03-variables/README.md) | Store, name, update, and protect (`const`) data |
| 4 | [Control Structures](04-control-structures/README.md) | Make decisions (`if`) and repeat work (loops) |
| 5 | [Data Structures](05-data-structures/README.md) | Group many values with arrays, `vector`, `string`, and `struct` |
| 6 | [Functions I](06-functions-i/README.md) | Break a program into reusable, named pieces |
| 7 | [Functions II](07-functions-ii/README.md) | Use recursion, pass-by-reference, and overloading |
| 8 | [Classes and Objects](08-classes-and-objects/README.md) | Design your own types with data + behavior bundled together (OOP) |
| 9 | [Capstone Project](09-capstone-project/README.md) | Combine everything into one real program, built and committed in stages |

Each Part 1 module builds toward its **capstone**: a Student Records &
Grading System you'll grow piece by piece, committing your progress to
GitHub at every stage — so by the end you'll have a real project in your
GitHub portfolio, not just scattered exercises.

### Part 2 — Intermediate C++

Picks up exactly where Part 1's capstone leaves off. Every module's hook
project is offered as three tracks — **Generic**, **Electrical/Electronic
Engineering**, and **Biomedical Engineering** — so you can apply each new
concept to your own field; pick whichever track fits you, or try more
than one.

| # | Module | You will be able to... |
|---|--------|------------------------|
| 10 | [Pointers & Dynamic Memory](10-pointers-dynamic-memory/README.md) | Use addresses/pointers directly and allocate runtime-sized memory with `new`/`delete` |
| 11 | [Inheritance](11-inheritance/README.md) | Derive one class from another to model "is-a" relationships and reuse behavior |
| 12 | [Polymorphism & Virtual Functions](12-polymorphism/README.md) | Use `virtual` so a mixed collection of derived objects is handled correctly through one base-class interface |
| 13 | [Operator Overloading](13-operator-overloading/README.md) | Make your own classes support `+`, `==`, `<<`, and other natural syntax |
| 14 | [File I/O](14-file-io/README.md) | Read and write files so data persists across program runs |
| 15 | [Exception Handling](15-exception-handling/README.md) | Use `try`/`catch`/`throw` to handle bad input and unsafe conditions gracefully |
| 16 | [STL: Containers & Iterators](16-stl-containers/README.md) | Use `map`/`set` and iterators to pick the right container for a problem |
| 17 | [STL Algorithms & Lambdas](17-stl-algorithms-lambdas/README.md) | Use `sort`/`find`/`transform`/`count_if` and lambda functions instead of hand-written loops |
| 18 | [Templates](18-templates/README.md) | Write generic functions and classes that work across types |
| 19 | [Capstone Project 2](19-capstone-project-2/README.md) | Combine every Part 2 concept into one real, staged, track-based project |

Part 2's capstone offers the same three tracks — Generic, EE, and
Biomedical — each extending or paralleling the Part 1 capstone with
inheritance, file persistence, exception safety, STL containers, and
generic templates.

## Ground rules for how we'll work

- **Type the code yourself.** Copy-pasting defeats the purpose — your
  fingers and your mistakes are how the syntax sticks.
- **Read every compiler error fully**, top to bottom, before asking for
  help. The first error in a long list is usually the real one; everything
  after it is often noise caused by that first mistake.
- **Compile often.** Write 3–5 lines, then compile. Don't write 100 lines
  and try to debug them all at once.
- **Commit often.** After finishing an example, exercise, or project step,
  commit it. Module 0 shows you exactly how. Small, frequent commits are a
  professional habit you're building from day one.

## Prerequisites

None, other than curiosity and a willingness to make (and fix) mistakes.
Mistakes are not a sign you're bad at this — they're the main way anyone
learns to program. Start with [Module 0: Setup](00-setup/README.md).
