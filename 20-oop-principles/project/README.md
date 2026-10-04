# Module 20 Project — Design First, Then Code

Pick **one** track. Every track follows the same two steps, because
that's the habit this module is building: **design on paper first,
then write code that matches the design.**

The three tracks introduced here are the **same three systems you'll
grow throughout Part 3**, all the way to Capstone Project 3 in Module
36. Pick the one you'd most like to keep working on.

**Step 1 — Design (`DESIGN.md`)**. Create a file called `DESIGN.md` in
this `project/` folder containing:

1. Your track's problem statement (copied from below).
2. A noun/verb analysis table: each noun marked as *class*,
   *attribute*, or *neither*, with a one-line reason.
3. One CRC card per class (responsibilities + collaborators).
4. A text UML class diagram showing every class with its `+`/`-`
   members.

**Step 2 — Code**. Implement the classes from your design in your
chosen starter file, so that `main` runs the scenario described.

## Track A — Generic: School Club Registry

> "A school runs after-school clubs, such as a Robotics Club and a
> Coding Club. Each club has a name, a patron teacher, and a maximum
> number of members. A student, who has a name and a class (for example
> 'JHS 2'), can join a club only if it isn't full and they aren't
> already a member. The club records attendance for each meeting, and
> the patron can print a register showing how many meetings each member
> attended."

Your `main` must: create two clubs, add students (including one refused
because the club is full and one refused as a duplicate), record at
least three meetings of attendance, and print each club's register.

## Track B — Electrical/Electronic Engineering: Home Energy Monitor

> "A household wants to understand its electricity bill. The house has
> several rooms. Each room contains appliances, such as a fridge, a
> fan, or a television. Each appliance has a name, a power rating in
> watts, and the number of hours it runs per day. The monitor calculates
> each appliance's daily energy use in kilowatt-hours, each room's
> total, and the whole house's total, and estimates the monthly cost
> using a tariff in Ghana cedis per kWh."

Use `energy (kWh) = power (W) x hours / 1000`. Your `main` must:
create at least two rooms with at least two appliances each, reject an
appliance with a negative power rating or more than 24 hours per day,
and print a per-room and whole-house report including the monthly
(30-day) cost.

## Track C — Biomedical Engineering: Clinic Appointment System

> "A small clinic books appointments. Each patient has a name, a folder
> number, and a date of birth. Each doctor has a name and a speciality.
> An appointment links one patient to one doctor at a time slot (for
> example '09:00'). A doctor can never have two appointments in the same
> time slot. The receptionist can print a doctor's schedule for the day,
> listing each time slot and the patient booked into it."

Your `main` must: create two doctors and at least three patients, book
several appointments, prove that double-booking a doctor's slot is
refused, and print each doctor's schedule.

## Starter files

- [`generic_starter.cpp`](generic_starter.cpp)
- [`ee_starter.cpp`](ee_starter.cpp)
- [`biomedical_starter.cpp`](biomedical_starter.cpp)

The starters give you class *names only* — deciding the members is
your job, and should come from your `DESIGN.md`, not the other way
round.

## When you're done

```bash
g++ -std=c++17 -Wall -Wextra <your_chosen_starter>.cpp -o design_project
./design_project
```

Your build should produce **zero warnings**.

```bash
git add 20-oop-principles
git commit -m "Complete Module 20 project: design document and model"
git push
```
