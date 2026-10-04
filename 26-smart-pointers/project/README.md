# Module 26 Project — Ownership Made Visible

Continue your track. Your system now has a **polymorphic hierarchy**
(Modules 11–12), **objects that move between owners**, and
**objects that are referred to from several places**. In this project
you'll express every one of those relationships with the right smart
pointer — and you will not write `new` or `delete` anywhere.

## Requirements (all tracks)

**Part 1 — `unique_ptr` and a polymorphic collection.**
1. Complete the hierarchy in your starter: a base class with a
   `virtual` destructor and `virtual` methods, plus the derived classes
   listed for your track. The starters mark the base methods `= 0`
   (*pure virtual* — previewed in Module 12, covered fully in Module
   29): it simply means every derived class **must** provide its own
   version, and the base class can't be created on its own.
2. Store them in a `std::vector<std::unique_ptr<Base>>` owned by your
   track's container class, created with `std::make_unique`.
3. Print a report with **one** polymorphic loop.

**Part 2 — Transferring ownership.**
4. Add a method that **removes** an object from one container and
   **returns** it as a `std::unique_ptr<Base>`, and a method that
   **takes** a `std::unique_ptr<Base>` and stores it. Use them to move
   one object from one container to another, and show that it is
   deleted exactly once, by its *new* owner.
5. Every function that only *uses* an object must take a reference (or
   a raw pointer if "none" is allowed) — never a smart pointer.

**Part 3 — `shared_ptr` and `weak_ptr`.**
6. Model the relationship described for your track with
   `std::shared_ptr` (owner side) and `std::weak_ptr` (observer side).
7. Show, with output, that when the owners let go, the observers
   correctly report that the object is gone (`lock()` returns empty) —
   and that nothing leaks (every `[-]` destructor message appears).

**Part 4 — Check.**
8. `grep -n "new \|delete " src/*.cpp include/*.h` must find nothing
   (apart from comments).
9. Build with `-fsanitize=address` and confirm there are no errors or
   leaks.
10. In a comment at the top of `main.cpp`, list every pointer-like
    member or parameter in your program and say, for each, whether it
    **owns**, **shares**, **observes**, or **borrows** — and why.

## Track A — Generic: School Staff, Students & Clubs

- **Hierarchy:** `StaffMember` (base: name, `virtual double
  monthlySalaryGhs() const`, `virtual std::string role() const`) →
  `Teacher` (base salary + allowance per subject taught) and
  `Administrator` (fixed salary). `School` owns staff in a
  `std::vector<std::unique_ptr<StaffMember>>`.
- **Transfer:** a teacher is transferred from one `School` (campus) to
  another: `std::unique_ptr<StaffMember> release(std::string name)` and
  `void hire(std::unique_ptr<StaffMember>)`.
- **Shared / weak:** students are owned by the school roll as
  `std::shared_ptr<Student>`. Each `Club` keeps a
  `std::vector<std::weak_ptr<Student>>` of members — a club doesn't
  keep a student alive. When a student leaves the school, every club
  register shows "(left the school)" for them.

## Track B — Electrical/Electronic Engineering: Rooms and Appliances

- **Hierarchy:** `Appliance` (base: name, power in watts, `virtual
  double dailyKwh() const`) → `AlwaysOnAppliance` (24 h/day, e.g. a
  fridge), `TimedAppliance` (hours per day, e.g. a TV), and
  `ThermostaticAppliance` (an air conditioner whose compressor runs a
  *duty cycle* fraction of its hours, e.g. 60%). `Room` owns its
  appliances in a `std::vector<std::unique_ptr<Appliance>>`.
- **Transfer:** move an appliance from one room to another
  (`std::unique_ptr<Appliance> remove(std::string name)` and
  `void install(std::unique_ptr<Appliance>)`).
- **Shared / weak:** the `House` owns its rooms as
  `std::shared_ptr<Room>`. A `SmartPlug` monitoring device keeps a
  `std::weak_ptr<Room>` to the room it reports on. When a room is
  demolished (removed from the house), the plug reports "room no longer
  exists".

## Track C — Biomedical Engineering: Wards, Devices and Patients

- **Hierarchy:** `MedicalDevice` (base: serial number, `virtual
  std::string status() const`, `virtual bool needsAttention() const`) →
  `Thermometer`, `PulseOximeter`, and `InfusionPump`. `Ward` owns its
  devices in a `std::vector<std::unique_ptr<MedicalDevice>>`.
- **Transfer:** move a device from one ward to another, e.g. a pulse
  oximeter borrowed by the Emergency ward
  (`std::unique_ptr<MedicalDevice> lend(std::string serial)` and
  `void receive(std::unique_ptr<MedicalDevice>)`).
- **Shared / weak:** admitted patients are owned by the ward's
  admission list as `std::shared_ptr<Patient>`. Each device keeps a
  `std::weak_ptr<Patient>` to the patient it's attached to. When a
  patient is discharged, devices still attached report "patient
  discharged — detach device".

## Starter folders

- [`generic_starter/`](generic_starter/)
- [`ee_starter/`](ee_starter/)
- [`biomedical_starter/`](biomedical_starter/)

## When you're done

```bash
git add 26-smart-pointers
git commit -m "Complete Module 26 project: ownership with smart pointers"
git push
```
