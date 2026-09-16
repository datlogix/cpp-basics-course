# Module 19 — Capstone Project 2

Part 1's capstone combined Modules 1–8 into a Student Records system.
This capstone does the same for Part 2: **pointers, inheritance,
polymorphism, operator overloading, file I/O, exceptions, STL
containers/algorithms, and templates**, combined into one real, staged
program. Pick **one** track below — all three exercise the same eight
concepts, applied to a different domain.

## Concept map — where each requirement traces back to

| Concept | Module | Where it appears here |
|---|---|---|
| Pointers, `new`/`delete` | 10 | Managing a collection of polymorphic objects |
| Inheritance | 11 | A base class with 2–3 derived types |
| Polymorphism, `virtual` | 12 | A `vector<Base*>` handled correctly with one loop |
| Operator overloading | 13 | A value-like class (e.g. `Complex`, `Dosage`) with natural `+`/`<<` |
| File I/O | 14 | Persisting records to a file across program runs |
| Exception handling | 15 | Rejecting invalid input/unsafe conditions without crashing |
| STL containers | 16 | A `map` keyed by name/ID holding a history of values |
| STL algorithms & lambdas | 17 | `sort`/`count_if`/`transform` used for analysis |
| Templates | 18 | A reusable `Statistics<T>` (or similar) applied generically |

## Track A — Generic: Extended Student Records & Grading System

Extend Part 1's capstone (`09-capstone-project/`) with everything from
Part 2:

**Stage 1 — Inheritance & Polymorphism**
1. Turn `Student` (from Part 1) into a base class with a `virtual`
   `letterGrade()` and `virtual ~Student()`.
2. Add derived classes `UndergraduateStudent` and `GraduateStudent`,
   each overriding `letterGrade()` with a different grading scale (your
   choice — e.g. graduate students need 70+ for a "B" instead of 80+).
3. Store students in a `vector<Student*>`, built with `new`, and print
   every student's report with one polymorphic loop.

**Stage 2 — File I/O, Exceptions, STL**
4. Persist the roster to a CSV file (`name,type,score1,score2,...`),
   reloading it at startup so records survive across runs
   (`std::ios::app` to add new students each run).
5. Throw and catch an exception for an out-of-range score (`0`–`100`)
   and for looking up a student who doesn't exist.
6. Replace any manual "find student" loop with a
   `std::map<std::string, Student*>` keyed by name.

**Stage 3 — Algorithms & Templates**
7. Use `std::sort` (or a `std::vector` copy sorted by average) to print
   students ranked highest to lowest.
8. Use `std::count_if` to count how many students are on the "honor
   roll" (e.g. average ≥ 90).
9. Build a `Statistics<double>` (from Module 18) fed every student's
   average, and print the class's mean and standard deviation.
10. `delete` every pointer before the program ends.

## Track B — Electrical/Electronic Engineering: Digital Multimeter & Data Acquisition System

**Stage 1 — Inheritance & Polymorphism**
1. Build (or reuse from Modules 11/12) a `Component` hierarchy —
   `Resistor`, `Capacitor`, `Inductor` — with `virtual describe()`,
   `virtual impedance(double frequencyHz)`, and `virtual ~Component()`.
2. Store components in a `vector<Component*>`, built with `new`, and
   print every component's impedance at a chosen frequency with one
   polymorphic loop.

**Stage 2 — File I/O, Exceptions, STL**
3. Log every reading session to a CSV file (`timestamp,node,voltage`),
   appending across runs.
4. Throw and catch exceptions for invalid component values (e.g.
   negative resistance) and for an overcurrent condition
   (`current = voltage / resistance` exceeding a safe maximum).
5. Store live sample history in a
   `std::map<std::string, std::vector<double>> nodeSamples` keyed by
   node name.

**Stage 3 — Algorithms & Templates**
6. Use `std::max_element`/`std::min_element` to report the peak and
   lowest voltage per node.
7. Use `std::count_if` to count over-voltage events across all logged
   samples.
8. Build a `Statistics<double>` (from Module 18) fed a node's sample
   history, printing mean and standard deviation (flagging a "noisy"
   node past a threshold you choose).
9. `delete` every `Component*` before the program ends.

## Track C — Biomedical Engineering: Patient Monitoring & Records System

**Stage 1 — Inheritance & Polymorphism**
1. Build (or reuse from Modules 11/12) a `MedicalDevice` hierarchy —
   `Thermometer`, `PulseOximeter`, `ECGMonitor` — with
   `virtual printReading()` and `virtual ~MedicalDevice()`.
2. Store devices in a `vector<MedicalDevice*>`, built with `new`, and
   print a unified patient dashboard with one polymorphic loop.

**Stage 2 — File I/O, Exceptions, STL**
3. Persist every reading to a patient record file
   (`patientId,deviceType,value`), appending across runs so a patient's
   history accumulates over multiple sessions.
4. Throw and catch exceptions for an invalid/out-of-range vital sign and
   for a calculated dosage (reuse `Dosage` from Module 13/15) exceeding
   a safe maximum.
5. Store each patient's reading history in a
   `std::map<std::string, std::vector<double>> patientReadings` keyed
   by patient ID.

**Stage 3 — Algorithms & Templates**
6. Use `std::count_if` to count abnormal readings (outside a healthy
   range you define per vital sign) across a patient's whole history.
7. Use `std::transform` to convert a patient's raw readings into a
   "risk score" series (distance from a healthy baseline).
8. Build a `Statistics<double>` (from Module 18) fed a patient's
   reading history, printing mean and standard deviation (flagging an
   "unstable" patient past a threshold you choose).
9. `delete` every `MedicalDevice*` before the program ends.

## Starter files

- [`generic_starter.cpp`](generic_starter.cpp)
- [`ee_starter.cpp`](ee_starter.cpp)
- [`biomedical_starter.cpp`](biomedical_starter.cpp)

Each is scaffolded with the class hierarchy stubbed in and `TODO`
markers matching the three stages above. Commit after **each stage**,
exactly as in the Part 1 capstone — this is a habit worth keeping for
every real project you build after this course, not just here.

```bash
git add 19-capstone-project-2
git commit -m "Capstone 2 stage 1: <your track>'s class hierarchy"
# ... work through stage 2 ...
git commit -m "Capstone 2 stage 2: file I/O, exceptions, STL container"
# ... work through stage 3 ...
git commit -m "Capstone 2 stage 3: algorithms, templates, cleanup"
git push
```

## You're done when...

- The program compiles and runs with no crashes on normal use, and
  handles bad input/unsafe conditions gracefully via exceptions instead
  of crashing.
- Every dynamically allocated object is `delete`d — no leaks.
- Records genuinely persist across separate runs of the program.
- Your GitHub repository shows at least 3 new commits for this module.

## Where to go from here

You now have a solid, practical grounding in intermediate C++. Natural
next steps beyond this course: smart pointers (`std::unique_ptr`,
`std::shared_ptr`) to replace raw `new`/`delete` entirely, multiple
inheritance and interfaces, move semantics and `std::move`, multi-file
projects with headers and a build system (CMake), and unit testing
(e.g. with Catch2 or GoogleTest). Keep committing to GitHub as you
explore — the habit built across both parts of this course is worth
more, long-term, than any single topic in it.
