# Module 33 Project — Refactor a God Class

Continue your track. Each starter contains a program that **works** but
was written in a hurry: one enormous "manager" class that does
everything. It's exactly the kind of code you'll meet in real jobs.

Your job is to **refactor** it into a clean, SOLID design — **without
changing its output** — and then prove the new design is easy to extend.

## Requirements (all tracks)

**Step 1 — Safety net.** Build and run the starter, and save its output:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o program
./program > before.txt
```

Commit the untouched starter before you change anything.

**Step 2 — Diagnosis (`SMELLS.md`).** List every smell you can find
(use the table in the module README): where it is, which SOLID
principle it breaks, and how you plan to fix it. Aim for at least
**eight**.

**Step 3 — Refactor in small steps.** Move towards a design where:

- every class has **one responsibility** (SRP);
- behaviour that varies by "type" is chosen by **polymorphism**, not a
  `switch` or `if` chain on a string or enum (OCP);
- no subclass refuses or weakens what its base promises (LSP);
- interfaces are **small and focused** (ISP);
- the high-level class receives its **output channel** (notifier,
  alarm, logger) and anything else that talks to the outside world as
  an **interface reference through its constructor** (DIP);
- one class per `.h`/`.cpp` pair, in a namespace (Module 22), with
  smart pointers for ownership (Module 26).

After **every** step: build, run, and `diff before.txt after.txt` must
print nothing. **Commit each successful step** with a message that says
what you did (e.g. "Extract Menu class from CanteenManager").

**Step 4 — Prove it's open for extension.** Once the output is
identical, add the **new features** listed for your track. These should
be done almost entirely by **adding new classes** — in
`REFACTORING.md`, list every *existing* file you had to edit for the
new features, and justify each edit.

**Step 5 — `REFACTORING.md`.** Also include: a before/after UML
sketch, the list of your refactoring commits, and a short paragraph:
*"Which principle made the biggest difference to this code, and why?"*

## Track A — Generic: `SchoolManager`

The god class stores students, records assessment results (with a
`switch` on assessment type to work out weighted marks), calculates
fees with discounts (an `if` chain on scholarship type), prints report
cards, and "texts" parents through a concrete `SmsGateway` it creates
itself.

**New features (Step 4):** a new assessment type, **Practical**
(robotics practical, weight 0.3, marked out of 50); a new scholarship
type, **Sibling** (10% off for the second child); and an
**EmailGateway** for parents who prefer email.

## Track B — Electrical/Electronic Engineering: `EnergyController`

The god class stores appliances, calculates daily energy with a
`switch` on appliance type, prices it with an `if` chain on the tariff
band (lifeline / residential / commercial), decides load-shedding
priority, prints the bill, and sounds alarms through a concrete
`Buzzer` it creates itself.

**New features (Step 4):** a new appliance type, **SolarInverter**
(which *produces* rather than consumes energy — careful: does it
satisfy LSP for "appliance"? Design accordingly); a **TimeOfUse** tariff
(peak/off-peak); and an **SmsAlarm** alongside the buzzer.

## Track C — Biomedical Engineering: `WardManager`

The god class stores patients, classifies vital signs with a `switch`
on vital type, calculates an early warning score, prints the shift
handover, and alerts staff through a concrete `Pager` it creates
itself.

**New features (Step 4):** a new vital sign, **respiratory rate**
(normal 12–20 breaths/min; score 3 below 9 or above 24, score 2 from 21
to 24, score 1 from 9 to 11); a new **paediatric** scoring scheme for
children's wards; and an **SmsAlert** channel alongside the pager.

## Starter folders

- [`generic_starter/`](generic_starter/)
- [`ee_starter/`](ee_starter/)
- [`biomedical_starter/`](biomedical_starter/)

## When you're done

```bash
git add 33-solid-principles
git commit -m "Complete Module 33 project: SOLID refactoring"
git push
```
