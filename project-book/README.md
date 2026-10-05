# Project Book — Starter Files (Part 1)

This folder holds the starter files for the **C++ Foundations Project Book**
(`Teaching Manuals/student-project-book/Foundations-CPP-Student-Project-Book.pdf`).
The book has the full instructions for every activity; this folder gives you
a file to start each one in.

| Folder | Book chapter | Starter files |
|--------|--------------|---------------|
| [`module-00/`](module-00/) | 0 — Tools, Git & GitHub | `ABOUT-ME.md`, `NOTES.md` |
| [`module-01/`](module-01/) | 1 — Basics of Programming | `timetable.cpp`, `receipt.cpp`, `ERRORS.md` |
| [`module-02/`](module-02/) | 2 — Data Types | `pick_the_right_type.cpp`, `trotro_fares.cpp`, `memory_map.cpp` |
| [`module-03/`](module-03/) | 3 — Variables | `introduce_yourself.cpp`, `momo_wallet.cpp`, `scope_detective.cpp` |
| [`module-04/`](module-04/) | 4 — Control Structures | `grade_checker.cpp`, `times_table_trainer.cpp`, `pattern_printer.cpp` |
| [`module-05/`](module-05/) | 5 — Data Structures | `weekly_rainfall.cpp`, `word_inspector.cpp`, `canteen_orders.cpp` |
| [`module-06/`](module-06/) | 6 — Functions I | `unit_converter.cpp`, `menu_calculator.cpp`, `grade_tracker_refactor.cpp` |
| [`module-07/`](module-07/) | 7 — Functions II | `swap_sort_summarise.cpp`, `printing_helpers.cpp`, `recursion_lab.cpp` |
| [`module-08/`](module-08/) | 8 — Classes and Objects | `library_book.cpp`, `phone_battery.cpp`, `football_league.cpp` |
| [`extended-capstone/`](extended-capstone/) | Extended Capstone | `school_reports.cpp`, `REFLECTION.md` |

## How to use a starter file

1. **Finish the module first.** Read its README, run its examples, and do its
   own exercise and project. The project book is extra practice, not a
   replacement for the lesson.
2. **Read the activity in the book**, then open its starter file here.
3. **Work through the `TODO` comments in order.** They follow the book's
   requirements, one by one. Compile after every one or two TODOs, not just
   at the end.
4. **Compile and run** from inside the module's folder, for example:

   ```bash
   cd project-book/module-04
   g++ grade_checker.cpp -o grade_checker
   ./grade_checker
   ```

   (On Windows, run `grade_checker.exe` instead of `./grade_checker`.)

5. **Commit when it works**, exactly as Module 0 taught you:

   ```bash
   git add project-book/module-04/grade_checker.cpp
   git commit -m "Project book: grade checker (Chapter 4, Activity 1)"
   git push
   ```

## What a starter file does and doesn't give you

Every starter compiles and runs as it is, but does nothing useful until you
complete it. It gives you:

- the `#include` lines you need;
- for later chapters, the `struct`, function and class **outlines** (names
  and parameters), with empty bodies for you to fill in;
- numbered `TODO` comments, one for each requirement in the book.

It never gives you the answer: there are **no solutions** in this folder.
Each starter's header also repeats the chapter's **"Use only"** line. If
you find yourself wanting something that isn't on that list, there is a
simpler way using what you already know.

The **domain twists** have no starter files of their own: copy the starter
of the activity you're twisting and adapt it.
