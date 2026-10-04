# Module 34 Project — Patterns in Your System

Continue your track. You'll add a set of features to your system, each
of which is naturally solved by one of the patterns from this module.
The goal isn't to use as many patterns as possible — it's to recognise
*which* problem each pattern solves, and use it there.

## Requirements (all tracks)

1. Implement the features listed for your track using **at least five
   patterns**, which must include **Factory**, **Strategy** and
   **Observer**, plus at least two of the others suggested.
2. Write `PATTERNS.md` with one section per pattern you used:
   - the **problem** in your system it solves (one or two sentences);
   - the **classes** that play each role (e.g. "Subject:
     `TemperatureSensor`; Observers: `Display`, `Automation`");
   - a small **text UML** sketch;
   - **what change it makes easy** — and show it: describe (or actually
     make, in a separate commit) one such change.
3. One section of `PATTERNS.md` must describe a place where you
   **decided not** to use a pattern, and why.
4. Ownership must be clear: `unique_ptr` for owned objects, references
   or raw pointers only for observing/borrowing (Module 26). Observers
   must unsubscribe before they're destroyed.
5. The starter's `main.cpp` contains a **scenario script**. Your program
   must run the whole scenario and print a clear trace of what
   happened.

## Track A — Generic: School Events Hub

| Feature | Suggested pattern |
|---|---|
| Create students, teachers and assessments from configuration lines | **Factory** |
| Grade reports with a choice of scheme: letter grades, WASSCE (A1–F9), or pass/fail | **Strategy** |
| When a result is published or a fee is paid, notify the parent SMS service, the head teacher's dashboard, and the audit log | **Observer** |
| Gradebook edits (enter score, correct score, add student) can be undone | **Command** |
| School → departments → classes, so "how many students?" works at any level | **Composite** |
| A readable way to set up a timetable entry with many optional fields | **Builder** |

## Track B — Electrical/Electronic Engineering: Smart Home Controller

| Feature | Suggested pattern |
|---|---|
| Create devices (lights, sockets, air conditioners, sensors) from a configuration file | **Factory** |
| Price energy with a choice of tariff: flat, lifeline, or time-of-use | **Strategy** |
| When a sensor reports (motion, temperature, door), run automations, update the app, and log the event | **Observer** |
| App and remote actions can be queued and undone | **Command** |
| An air conditioner with modes Off / Cooling / Eco / Fault and rules for moving between them | **State** |
| House → floors → rooms → devices, for energy totals at any level | **Composite** |
| A third-party Fahrenheit sensor with a different interface | **Adapter** |

## Track C — Biomedical Engineering: Ward Monitoring Platform

| Feature | Suggested pattern |
|---|---|
| Create monitors for each bed from a configuration file | **Factory** |
| Early warning scoring with a choice of scheme: adult or paediatric | **Strategy** |
| When a vital sign is recorded, update the nurse station, the early warning calculator, and the chart log | **Observer** |
| An infusion pump with modes Idle / Running / Paused / Alarm | **State** |
| Medication administration entries can be undone (with a reason) by the nurse in charge | **Command** |
| Optional smoothing and logging around raw sensor readings | **Decorator** |

## Starter folders

- [`generic_starter/`](generic_starter/)
- [`ee_starter/`](ee_starter/)
- [`biomedical_starter/`](biomedical_starter/)

Each starter contains the event interfaces and a scenario script to
get you going; the design of everything else is up to you.

## When you're done

```bash
git add 34-design-patterns
git commit -m "Complete Module 34 project: design patterns in my system"
git push
```
