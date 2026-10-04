# Module 23 Project — Guaranteed Clean-Up with RAII

Continue your track. Each track has a real-world **resource** that must
*always* be released, no matter how a piece of code exits — and a
scenario that exits early. You'll build an RAII class so that the
clean-up can't be forgotten.

Like every Part 3 project from Module 22 onwards, each starter is a
small multi-file CMake project:

```bash
cmake -S . -B build
cmake --build build
./build/<program name>
# or: g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o program
```

## Requirements (all tracks)

1. Add **tracing output** (`[+]`/`[-]` lines) to the constructor and
   destructor of your RAII class, so the output *proves* when the
   resource is acquired and released.
2. The RAII class must acquire the resource in its **constructor** and
   release it in its **destructor**. No `start()`/`stop()` or
   `open()`/`close()` calls in `main` or in the scenario functions.
3. Write a scenario function with **at least two early `return`s**, and
   run it with inputs that take every path. The output must show the
   resource released on every path.
4. Append a line to a log file from inside the RAII class (using
   `std::ofstream` with `std::ios::app`, from Module 14), so the log
   survives across runs.
5. In a comment at the top of `main.cpp`, explain in your own words why
   the RAII object must be an **automatic** (stack) object, not one
   created with `new`.
6. Do **not** copy your RAII objects — Module 24 is next.

## Track A — Generic: Club Attendance Session

A club meeting is a resource: once a meeting has been *opened* it must
always be *closed* in the attendance log, even if the meeting is
abandoned early (a fire drill, a power cut).

- Build `AttendanceSession` (`include/attendance_session.h`,
  `src/attendance_session.cpp`). Its constructor takes the club name
  and date, writes `OPEN <club> <date>` to `attendance_log.txt`. Its
  `markPresent(const Student&)` records a student. Its destructor
  writes `CLOSE <club> <date> - <n> present`.
- Scenario: `runMeeting(...)` marks students present one by one, but
  stops early if a student ID is invalid, or if a `"FIRE DRILL"` event
  happens part-way through the list.

## Track B — Electrical/Electronic Engineering: Bench Power Supply Guard

A bench power supply that has been switched on for a test **must**
always be switched off afterwards — leaving it on is a fire and safety
hazard.

- A simple `PowerSupply` class is provided (it just records its state
  and prints messages).
- Build `SupplyGuard` (`include/supply_guard.h`, `src/supply_guard.cpp`).
  Its constructor takes a `PowerSupply&` and a voltage, and switches
  the supply on. Its destructor switches it off and appends
  `test at <V> V: supply switched off safely` to `bench_log.txt`.
- Scenario: `testAppliance(PowerSupply&, double volts, double ohms)`
  calculates the current (`I = V / R`). It returns early if the
  resistance is zero or negative (short circuit), or if the current is
  above a `MAX_CURRENT_AMPS` limit (overcurrent). Otherwise it prints
  the power (`P = V x I`).

## Track C — Biomedical Engineering: Infusion Pump Session

An infusion pump that has been started **must** always be stopped —
a pump left running delivers an uncontrolled dose.

- A simple `InfusionPump` class is provided.
- Build `InfusionSession` (`include/infusion_session.h`,
  `src/infusion_session.cpp`). Its constructor takes an
  `InfusionPump&`, a patient folder number, and a rate in mL/h, and
  starts the pump. Its destructor stops the pump and appends
  `<folder>: pump stopped after <minutes> min` to `infusion_log.txt`.
- Scenario: `runInfusion(...)` steps through a list of minute-by-minute
  pressure readings. It returns early on an **occlusion** (pressure
  above a limit) or an **air-in-line** alarm (a reading of exactly
  `-1`). Otherwise it completes the planned duration.

## Starter folders

- [`generic_starter/`](generic_starter/)
- [`ee_starter/`](ee_starter/)
- [`biomedical_starter/`](biomedical_starter/)

## When you're done

```bash
git add 23-object-lifetime-raii
git commit -m "Complete Module 23 project: RAII resource guard"
git push
```
