# Module 21 Project — Redesign Your Core Classes

Continue the track you chose in Module 20. You'll take that track's
most important class and rebuild it **properly**, using every tool from
this module. The scenario is the same; the class just becomes much
harder to misuse.

Every track must demonstrate **all** of the following, and you should
add a short comment next to each one saying which Module 21 idea it
shows:

- a member initializer list for every constructor
- default member initializers for every built-in-type member
- at least one `const` data member
- a delegating constructor
- an `explicit` single-argument constructor
- `const` on every method that doesn't modify the object
- a clear invariant, written as a comment, enforced by every public
  method (no blind setters!)
- a `static` data member and a `static` method
- at least two methods defined outside the class with `ClassName::`

## Track A — Generic: School Club Registry, redesigned

Rebuild `Student` and `Club`:

1. `Student` gets an automatically assigned, **`const`** integer ID from
   a `static int nextId`. Its name and form (e.g. `"JHS 2"`) are set in
   the constructor; a delegating `explicit Student(std::string name)`
   defaults the form to `"Unassigned"`.
2. `Club`'s invariant: *member count never exceeds capacity, and no
   student ID appears twice.* Capacity is `const` and must be at least
   1 (fall back to 10 if a bad value is passed).
3. `Club` offers `join(const Student&)`, `leave(int studentId)`,
   `isMember(int studentId) const`, and `printRegister() const`.
4. A `static int totalMemberships()` on `Club` reports how many
   memberships exist across *all* clubs.

## Track B — Electrical/Electronic Engineering: Home Energy Monitor, redesigned

Rebuild `Appliance`:

1. `Appliance`'s name and power rating are `const`. Its invariant:
   *power rating is positive, and hours per day is between 0 and 24.*
   Invalid values in the constructor fall back to safe defaults (and
   print a warning).
2. A delegating `explicit Appliance(std::string name)` creates a 100 W
   appliance used 1 hour per day.
3. Instead of `setHours`, offer `bool useFor(double hours)` which
   validates the new value.
4. The electricity tariff is shared by every appliance, so make it a
   `static double tariffGhsPerKwh` with `static bool setTariff(double)`
   (rejecting zero or negative tariffs) and `static double getTariff()`.
5. `double dailyKwh() const` and `double monthlyCostGhs() const`
   (30 days, using the static tariff).

## Track C — Biomedical Engineering: Clinic Appointment System, redesigned

Rebuild `Patient`:

1. Folder numbers are generated automatically from a
   `static int nextFolder` and stored as a **`const std::string`**
   formatted like `"CL-0007"`.
2. `Patient`'s invariant: *name is never empty, and birth year is
   between 1900 and the current year.* Invalid values fall back to
   `"Unknown"` / the current year, with a warning.
3. A delegating `explicit Patient(std::string name)` is for walk-in
   patients whose birth year is not yet known (use the current year and
   mark them `needsDetails`, a `bool` with a default member value).
4. `int ageInYear(int year) const`, and `bool completeDetails(int
   birthYear)` which validates and clears `needsDetails`.
5. A `static int patientsRegistered()`.

## Starter files

- [`generic_starter.cpp`](generic_starter.cpp)
- [`ee_starter.cpp`](ee_starter.cpp)
- [`biomedical_starter.cpp`](biomedical_starter.cpp)

## When you're done

```bash
g++ -std=c++17 -Wall -Wextra <your_chosen_starter>.cpp -o class_design_project
./class_design_project
```

```bash
git add 21-class-design
git commit -m "Complete Module 21 project: redesigned core classes"
git push
```
