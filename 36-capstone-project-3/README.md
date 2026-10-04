# Module 36 — Capstone Project 3

Part 1's capstone built a Student Records system from Modules 1–8.
Part 2's capstone combined pointers, inheritance, polymorphism, file
I/O, exceptions, the STL and templates. This capstone brings together
**all of Part 3**: you'll design and build a real, multi-file,
object-oriented system — the same system you've been growing in your
track since Module 20 — the way a professional team would:

- **designed** on paper before it's coded,
- **organised** into namespaces, headers and source files, built with
  CMake,
- with **clear ownership** and **no manual memory management**,
- with **class hierarchies, interfaces and design patterns** where they
  genuinely help,
- **exception-safe**, with data that **persists** across runs,
- and **tested**, with sanitizers, before it's called finished.

It's built in **four stages**, each committed separately. Pick the same
track you've followed through Part 3 (you may switch, but you'll lose
the head start your earlier projects give you).

## Concept map — where each requirement traces back to

| Concept | Module | Where it appears in the capstone |
|---|---|---|
| OOP principles, noun/verb analysis, CRC cards, UML | 20 | `DESIGN.md` (Stage 1) |
| Invariants, `const` correctness, `explicit`, static members | 21 | Every core class |
| Multi-file layout, namespaces, CMake | 22 | The whole project structure |
| Lifetime, destructors, RAII | 23 | A session/log class that always closes cleanly |
| Copy semantics, Rule of Three | 24 | Deliberate copy decisions (`= delete` / Rule of Zero) |
| Move semantics, Rule of Five / Zero | 25 | Moving large objects into collections; no needless copies |
| Smart pointers and ownership | 26 | `unique_ptr` ownership; `shared_ptr`/`weak_ptr` only where justified |
| Composition, aggregation, association | 27 | The domain model's relationships (`DESIGN.md`) |
| Advanced inheritance | 28 | `final`, `override`, inheriting constructors; no slicing |
| Abstract classes and interfaces | 29 | A polymorphic hierarchy + at least two interfaces |
| Operator overloading II | 30 | A complete value type (`Money` / `Impedance`-style / `Dose`) |
| Exceptions in class design | 31 | Your own exception hierarchy; a strong-guarantee batch operation |
| Templates meet OOP | 32 | A constrained `Repository<T>` and `Statistics<T>` |
| SOLID | 33 | A SOLID review in `REFLECTION.md` |
| Design patterns | 34 | At least five patterns, documented in `PATTERNS.md` |
| Testing and debugging | 35 | A test suite (40+ checks), fakes, sanitizer-clean builds |
| File I/O (Part 2) | 14 | Data persists in CSV files across runs |
| STL containers and algorithms (Part 2) | 16–17 | `map`/`set`, `sort`, `count_if`, `transform` for reports |

## The four stages

The requirements below apply to **every** track. Your track's section
says *what* to build; these stages say *how well* it must be built.

### Stage 1 — Design and domain model

1. Write `DESIGN.md` **before** writing code:
   - your track's problem statement (below), and a noun/verb analysis;
   - a CRC card for every class;
   - a text UML class diagram showing every class with `+`/`-`
     members and every relationship (inheritance, composition,
     aggregation, association, dependency) with multiplicities;
   - an **ownership table**: for every pointer-like member, whether it
     owns, shares, observes, or borrows, and why.
2. Set up the project: `CMakeLists.txt` building the application **and**
   a test program; one `.h`/`.cpp` pair per class; everything in your
   track's namespace (`makersplace::school`, `makersplace::energy`,
   `makersplace::clinic`).
3. Implement the core **entity** classes and the **value type**, with
   invariants enforced in constructors and methods, `const` on every
   method that doesn't modify, and `explicit` single-argument
   constructors.

```bash
git commit -m "Capstone 3 stage 1: design and domain model"
```

### Stage 2 — Hierarchies, ownership and resources

4. Implement your track's **polymorphic hierarchy** with an abstract
   base class (pure virtual functions, virtual destructor, `override`
   everywhere, `final` where appropriate) and at least **two interfaces**
   (Module 29).
5. Store polymorphic objects in containers of `std::unique_ptr`. Use
   `std::shared_ptr`/`std::weak_ptr` **only** where your ownership table
   justifies it. **No `new` or `delete`** anywhere in your code.
6. Every class follows the **Rule of Zero**, or explicitly `= delete`s
   copying, with a comment saying why. Large objects are **moved**, not
   copied, into collections.
7. An **RAII class** guards one resource (a session log, a switched-on
   device, a running pump) so it's always released, even on an
   exception.

```bash
git commit -m "Capstone 3 stage 2: hierarchies, ownership and resources"
```

### Stage 3 — Behaviour, robustness and persistence

8. Your **value type** gets a complete, well-judged set of operators
   (Module 30) — including `<<`/`>>` and comparisons (or a documented
   reason for none).
9. Your own **exception hierarchy** (Module 31), with at least one
   exception carrying data; at least one **batch operation** with the
   **strong guarantee**; and `noexcept`-safe destructors.
10. A **`Repository<T>`** class template constrained by a **concept**
    (C++20), used for at least two different types, and a
    **`Statistics<T>`** used in at least one report (Module 32).
11. At least **five design patterns** (Module 34), including **Factory**,
    **Strategy** and **Observer**. Document each in `PATTERNS.md`.
12. **Persistence:** the system saves its data to CSV files and reloads
    it at start-up (Module 14), translating parse errors into your own
    `CorruptRecordError` with a line number, without one bad line
    stopping the rest.
13. A **menu-driven interface** (like Part 1's capstone) *and* a
    `--demo` mode (`./build/app --demo`) that runs a scripted scenario
    with no keyboard input, so anyone can see the whole system working.

```bash
git commit -m "Capstone 3 stage 3: behaviour, robustness and persistence"
```

### Stage 4 — Quality

14. A **test suite** of at least **40 checks** (Module 35 `minitest.h`,
    or Catch2), run through `ctest`, covering normal cases, boundaries,
    exceptions, and the strong guarantee — and using **fakes** for at
    least one interface (no real files, clocks or output channels in
    unit tests).
15. A build with `-g -fsanitize=address,undefined` runs the tests and
    the `--demo` scenario **with no sanitizer errors** and **no
    warnings** (`-Wall -Wextra`).
16. **`REFLECTION.md`** (400–700 words):
    - a **SOLID review**: one concrete example from your code for each
      principle — where you followed it, or where you knowingly didn't
      and why;
    - the **hardest design decision** you made, and what you'd do
      differently starting again;
    - which Part 3 module changed how you write code the most, and how.
17. A short `README.md` in your track folder: what the system does, how
    to build it, how to run the demo and the tests.

```bash
git commit -m "Capstone 3 stage 4: tests, sanitizers and reflection"
git push
```

---

## Track A — Generic: MakersPlace Academy Management System

> "MakersPlace Academy runs robotics, coding and STEAM programmes. The
> academy has **students**, **teachers** and **administrators**. Students
> enrol in **courses** (some courses have prerequisites and a maximum
> class size) and may join **clubs**. Each course has **assessments** —
> exams, coursework and practical projects — each graded out of a
> different total and weighted differently. The academy reports results
> using a **grading scheme** that can be changed (letter grades,
> WASSCE A1–F9, or pass/fail). Each student has a **fee account** in
> Ghana cedis: the academy charges fees, records payments and bursaries,
> and sends **reminders** to parents. When results are published or a
> payment is made, **parents**, the **head teacher's dashboard** and an
> **audit log** are all notified. Gradebook corrections can be
> **undone**. All records are kept between runs."

Minimum content:

- **Hierarchy:** `Person` → `Student`, `Teacher`, `Administrator`
  (abstract `Person`); `Assessment` → `Exam`, `Coursework`,
  `PracticalProject`.
- **Interfaces:** e.g. `Payable` (staff salaries), `Reportable`,
  `SchoolEventListener`.
- **Value type:** `Money` (pesewas internally).
- **Patterns:** Factory (people/assessments from CSV), Strategy (grading
  scheme), Observer (school events), Command (undoable gradebook edits),
  plus one more (Composite for academy → departments → courses, or
  Builder for timetable entries).
- **Strong guarantee:** `enrolMany(student, courses)`.
- **Reports:** a ranked course list (`sort`), honour-roll count
  (`count_if`), course statistics (`Statistics<double>`), and fees
  outstanding.

## Track B — Electrical/Electronic Engineering: Smart Home Energy Management System

> "A smart home is made of **floors** and **rooms**, each containing
> **devices**: lights, sockets, appliances, air conditioners and
> **sensors** (motion, temperature, door). Every room's devices sit on a
> **circuit** with a breaker rating; switching on a load that would trip
> the breaker must be refused. The system measures daily **energy use**
> at any level — device, room, floor or whole house — and prices it
> with a **tariff** that can be changed (flat, lifeline, time-of-use).
> When a sensor reports an event, **automations**, the **phone app** and
> an **event log** all react. An air conditioner moves between modes
> (**Off, Cooling, Eco, Fault**) according to clear rules. Actions from
> the app can be **queued and undone**. When demand exceeds the
> available supply, low-priority loads are **shed**. All configuration
> and energy logs are kept between runs."

Minimum content:

- **Hierarchy:** `Device` → `Light`, `Socket`, `AirConditioner`,
  `Sensor` (and `Sensor` → `MotionSensor`, `TemperatureSensor`,
  `DoorSensor`).
- **Interfaces:** e.g. `Switchable`, `Measurable` (energy),
  `SensorListener`.
- **Value type:** `Energy` or `Power` (with units and natural
  arithmetic), or a complex `Impedance` if your design uses it.
- **Patterns:** Factory (devices from configuration), Strategy (tariff),
  Observer (sensor events), State (air conditioner), Composite (house →
  floors → rooms → devices), plus Command (undoable app actions) if
  you can.
- **Strong guarantee:** `applySchedule(changes)` — all switching
  changes, or none.
- **Reports:** energy per room (`sort`), devices over budget
  (`count_if`), daily cost under two tariffs, and `Statistics<double>`
  of hourly demand.

## Track C — Biomedical Engineering: Hospital Ward Patient Monitoring System

> "A hospital has **wards** made of **beds**. **Patients** are admitted
> to beds and can be transferred between wards. Each bed has
> **monitors** — heart rate, SpO2, temperature, blood pressure — and some
> beds have an **infusion pump**. Raw monitor readings may be
> **smoothed** and **logged** before use. When a vital sign is recorded,
> the **nurse station**, the **early warning score (EWS)** calculator and
> the **observation chart** all react. The EWS uses a **scoring scheme**
> that depends on the ward (adult or paediatric). An infusion pump moves
> between modes (**Idle, Running, Paused, Alarm**) according to strict
> rules. Medication orders are checked against **allergies** and **daily
> dose limits**; a ward round's orders are all accepted or all
> rejected. Charting entries can be **undone** with a reason. All
> records are kept between runs."
>
> *(All clinical rules in this project are simplified for teaching and
> must not be used for real patient care.)*

Minimum content:

- **Hierarchy:** `MedicalDevice` → `VitalSignMonitor` (→
  `HeartRateMonitor`, `SpO2Monitor`, `TemperatureMonitor`,
  `BloodPressureMonitor`) and `InfusionPump`.
- **Interfaces:** e.g. `Alarmable`, `Chartable`, `VitalSignListener`.
- **Value type:** `Dose` (micrograms internally).
- **Patterns:** Factory (monitors from bed configuration), Strategy
  (EWS scoring scheme), Observer (vital signs), State (infusion pump),
  Decorator (smoothing/logging around readings), plus Command
  (undoable chart entries) if you can.
- **Strong guarantee:** `prescribeAll(patient, orders)` and
  `transfer(patient, toBed)`.
- **Reports:** patients ranked by EWS (`sort`), number of abnormal
  readings (`count_if`), `Statistics<double>` per vital sign, and a
  shift handover.

---

## Starter folders

- [`generic_starter/`](generic_starter/)
- [`ee_starter/`](ee_starter/)
- [`biomedical_starter/`](biomedical_starter/)

Each starter is a **scaffold**, not a solution: a CMake project that
builds an application and a test program, the namespace and folder
layout, `minitest.h`, a `--demo`/menu `main.cpp` skeleton, and a few
key headers (the abstract base class, the observer interface, the
exception root, the `Repository<T>` concept) to show the intended
shape. Everything else is yours to design — start with `DESIGN.md`.

```bash
cd 36-capstone-project-3/<track>_starter
cmake -S . -B build
cmake --build build
./build/app --demo
ctest --test-dir build --output-on-failure
```

## You're done when...

- `DESIGN.md`, `PATTERNS.md`, `TESTING.md`, `REFLECTION.md` and your
  track `README.md` are complete and match the code.
- The application builds with **zero warnings**, and both the `--demo`
  run and the test suite are **clean under AddressSanitizer and
  UBSan**.
- There is **no `new` or `delete`** in your code, and no raw pointer
  owns anything.
- Data genuinely **persists** across separate runs, and a corrupted line
  in a data file is reported and skipped, not fatal.
- The test suite has **40+ checks**, all passing through `ctest`.
- Your GitHub repository shows at least **four** commits for this
  module — one per stage — and ideally many more, smaller ones.

## Where to go from here

You've now completed all three parts of the course: from your first
`Hello, World!` to a designed, tested, multi-file object-oriented
system. Natural next steps:

- **Concurrency** — `std::thread`, `std::mutex`, `std::async`: doing
  several things at once (and why RAII locks matter).
- **More of the modern standard library** — `std::optional`,
  `std::variant`, `std::string_view`, `std::span`, ranges (C++20), and
  `std::format` (C++20/23).
- **Embedded C++ and robotics** — Arduino and ESP32 programming, where
  RAII, `constexpr`, templates and careful ownership really shine on
  small devices; or ROS 2 for robot software.
- **Graphical and networked applications** — Qt for desktop apps, or a
  web/REST library to put your system online.
- **Software engineering practice** — continuous integration (running
  your tests automatically on every push with GitHub Actions), code
  review, and contributing to open-source C++ projects.

Keep building, keep testing, and keep committing. The habits you've
practised across all three parts — small steps, clear ownership,
honest tests, and a design you can explain — are what make a
professional programmer.
