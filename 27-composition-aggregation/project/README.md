# Module 27 Project — Modelling Relationships Properly

Continue your track. Your system now has enough classes that the
*relationships between them* matter as much as the classes themselves.
In this project you'll design those relationships deliberately, draw
them, implement each one with the matching C++ technique, and fix a
design that misuses inheritance.

## Requirements (all tracks)

**Part 1 — Design (`DESIGN.md`).** Before writing code, add a
`DESIGN.md` to your starter folder with:

1. A text UML diagram of every class in your track's model (below),
   using the correct symbol for each relationship — `<*>---`
   composition, `<>---` aggregation, `----` association, `- - ->`
   dependency, `----|>` inheritance — **with multiplicities**.
2. A table with one row per relationship: *the two classes, the kind of
   relationship, how it's implemented in C++ (value member,
   `unique_ptr`, raw pointer, reference, `weak_ptr`, parameter), and a
   one-sentence justification based on lifetime.*

**Part 2 — Implement.** The starter puts every class skeleton in one
header, `include/model.h`, to get you going.

3. Split it into **one header and one source file per class** (Module
   22), with forward declarations wherever a header only needs a
   pointer or reference to another class. Update `CMakeLists.txt`.
4. Implement every relationship exactly as your `DESIGN.md` says.
5. Every two-way association must be changed through **one method**
   that updates both sides.
6. Add tracing destructors to show that composed parts die with their
   whole, and aggregated parts don't.

**Part 3 — Composition over inheritance.** The starter contains one
class that wrongly **inherits** from a standard container. Rewrite it
to **contain** the container instead, exposing only the operations that
make sense and enforcing the rule given in the starter's comment.
Explain in a comment what could go wrong with the old version.

**Part 4 — Run the scenario** described for your track in `main.cpp`.

## Track A — Generic: School Structure

| Class | Notes |
|---|---|
| `School` | composed of `Classroom`s (a school's classrooms are demolished with it) |
| `Classroom` | composed of one `Timetable` |
| `Course` | aggregates `Student`s (students exist independently; one student takes many courses) |
| `Teacher` ↔ `Course` | two-way association: a teacher teaches several courses; each course knows its one teacher |
| `ReportCardPrinter` | depends on `Course` (prints a course list from a parameter) |
| `Gradebook` | **Part 3:** currently `class Gradebook : public std::vector<double>`. Rule: scores must be 0–100. |

Scenario: build a school with two classrooms, three courses, two
teachers and five students; reassign one course to the other teacher
(both sides updated!); print each course's register; destroy a course
and show the students survive.

## Track B — Electrical/Electronic Engineering: Smart Home Wiring

| Class | Notes |
|---|---|
| `House` | composed of `Room`s |
| `Room` | composed of one `Thermostat` and one `LightingCircuit` |
| `EnergyMeter` | aggregates `Appliance`s from any rooms, to monitor them (doesn't own them; appliances are owned by their rooms in a `std::vector<std::unique_ptr<Appliance>>`) |
| `Electrician` ↔ `House` | two-way association: a service contract — an electrician services several houses; each house knows its one electrician |
| `BillCalculator` | depends on `EnergyMeter` (calculates a bill from a parameter) |
| `Circuit` | **Part 3:** currently `class Circuit : public std::vector<double>` holding load currents in amps. Rule: total current must never exceed the circuit breaker rating (e.g. 20 A); a load that would exceed it is refused. |

Scenario: build a house with three rooms, attach appliances to the
meter from two rooms, switch the service contract to a different
electrician (both sides updated!), print a bill, and show that removing
the meter doesn't delete any appliance.

## Track C — Biomedical Engineering: Hospital Structure

| Class | Notes |
|---|---|
| `Hospital` | composed of `Ward`s |
| `Ward` | composed of `Bed`s |
| `CareTeam` | aggregates `Nurse`s (nurses exist independently and may be on several teams) |
| `Bed` ↔ `Patient` | two-way association: a bed holds at most one patient; a patient is in at most one bed |
| `HandoverReport` | depends on `Ward` (prints a shift handover from a parameter) |
| `VitalsLog` | **Part 3:** currently `class VitalsLog : public std::vector<double>` of temperatures. Rule: readings must be between 30 and 45 °C, and readings may only be *added*, never edited or erased (it's part of the medical record). |

Scenario: build a hospital with two wards of three beds each; admit
patients to beds; **transfer** a patient to a bed in the other ward
(both sides updated!); print a handover report for each ward; disband a
care team and show the nurses survive.

## Starter folders

- [`generic_starter/`](generic_starter/)
- [`ee_starter/`](ee_starter/)
- [`biomedical_starter/`](biomedical_starter/)

## When you're done

```bash
git add 27-composition-aggregation
git commit -m "Complete Module 27 project: modelled relationships"
git push
```
