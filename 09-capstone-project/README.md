# Module 9 — Capstone Project: Student Records & Grading System

This is where every module in the course comes together into one real
program: **a console app that manages students and their grades.** You'll
build it in three committed stages, mirroring how real projects grow
incrementally rather than getting written in one sitting.

## What you're building

A menu-driven program with two classes:

- **`Student`** — one student's name and their list of scores.
- **`Classroom`** — holds many `Student`s and answers questions about the
  whole group (top student, class average, etc).

## Concept map — where each module shows up

| Concept | Module | Where it appears here |
|---|---|---|
| Compiling, `main`, `std::cout`/`cin` | 1, 3 | The whole program |
| Types (`double`, `std::string`, `bool`) | 2 | Scores, names, return values |
| `const`, input validation | 3 | Menu bounds, grade constants |
| `if`/`switch`/loops | 4 | The menu, grade lookup, input loops |
| `std::vector`, `struct`-style grouping | 5 | `Student`'s scores, `Classroom`'s students |
| Functions, prototypes | 6 | Free helper functions like `letterGrade` |
| Pass by reference, recursion | 7 | Updating scores in place; a recursive search (stretch goal) |
| Classes, encapsulation, constructors | 8 | `Student` and `Classroom` themselves |

## Stage 1 — The `Student` class

1. `Student` has private `std::string name` and `std::vector<double> scores`.
2. Constructor takes the name; scores start empty.
3. `void addScore(double score)` — appends a score, but **rejects**
   scores outside `0-100` (print an error, don't add it). This is
   exactly the kind of rule encapsulation exists to enforce.
4. `double average()` — returns the average of `scores` (return `0` if
   there are no scores yet — guard against dividing by zero).
5. `std::string letterGrade()` — uses `average()` and `if`/`else if` to
   return `"A"` (90+), `"B"` (80+), `"C"` (70+), `"D"` (60+), or `"F"`.
6. `void printReport()` — prints the name, average, and letter grade,
   nicely formatted.

**Commit this stage before moving on:**

```bash
git add 09-capstone-project
git commit -m "Capstone stage 1: Student class"
git push
```

## Stage 2 — The `Classroom` class + a working menu

1. `Classroom` has a private `std::vector<Student>`.
2. `void addStudent(std::string name)` — creates and stores a new
   `Student`.
3. `Student* findStudent(std::string name)` — searches the vector for a
   student by name, returning a pointer to it if found, `nullptr`
   otherwise. *(This is your first look at a pointer — used here only
   because "found nothing" needs a way to be represented, which a plain
   reference can't express. You don't need to master pointers generally
   to use this one pattern; the starter file shows exactly how.)*
4. `void printAllReports()` — calls `printReport()` on every student.
5. `double classAverage()` — averages every student's `average()`.
6. `std::string topStudent()` — returns the name of the student with the
   highest average.
7. Build a `main` with a loop and `switch` offering: Add Student, Add
   Score to a Student, Print All Reports, Show Class Average, Show Top
   Student, Exit.

**Commit this stage:**

```bash
git add 09-capstone-project
git commit -m "Capstone stage 2: Classroom class + menu"
git push
```

## Stage 3 — Polish (choose at least 2)

- **Input validation**: if the user types a name that doesn't exist when
  adding a score, print a clear message instead of crashing.
- **Sorting**: print all students ranked by average, highest first (a
  simple loop-based selection sort is fine — no need for anything
  fancy).
- **Recursive stretch goal**: write `Student* recursiveSearch(std::vector<Student>& students, std::string name, int index)`
  that searches for a name recursively instead of with a loop — base
  case: `index >= students.size()` returns `nullptr`.
- **Your own idea**: anything reasonable that uses what you've learned.

**Final commit:**

```bash
git add 09-capstone-project
git commit -m "Capstone stage 3: polish and validation"
git push
```

## Starter file

Open [`starter.cpp`](starter.cpp) — both classes are stubbed with
comments marking exactly which stage each TODO belongs to.

## You're done when...

- The program compiles and runs with no crashes on normal use.
- You can add students, add scores, and see correct averages/grades.
- Your GitHub repository shows at least 3 new commits for this module,
  one per stage — a real, visible record of how the project grew.

## Where to go from here

You now know enough C++ to read most beginner-to-intermediate tutorials,
build small tools, and keep learning independently. The natural next
step is **[Part 2: Intermediate C++](../README.md#part-2--intermediate-c)**,
starting at **[Module 10 — Pointers & Dynamic Memory](../10-pointers-dynamic-memory/README.md)**
— it picks up exactly where this capstone leaves off: pointers in
proper depth, inheritance and polymorphism (the next OOP topic after
this course's Classes and Objects), file I/O, exception handling, the
wider Standard Template Library (`std::map`, `std::set`, algorithms
like `std::sort`), and templates — with every module's project offered
in Generic, Electrical/Electronic Engineering, and Biomedical
Engineering tracks. Keep committing to GitHub as you go — that habit
only compounds in value from here.
