# Module 31 Project — An Exception-Safe Core

Continue your track. You'll give your system a proper **error model**:
its own exception hierarchy, operations that are **all-or-nothing**,
loading code that turns low-level failures into meaningful errors, and
clean-up that can never crash the program.

## Requirements (all tracks)

1. **Exception hierarchy.** One root class for your track (derived from
   `std::runtime_error`) and the specific exceptions listed below. At
   least **one** must carry extra data with getters (not just a message),
   and the catching code must *use* that data.
2. **Constructors enforce invariants** by throwing, and every class
   follows the Rule of Zero, so a throwing constructor can't leak.
   Prove it with a traced member, as in example 02.
3. **The strong guarantee** for the batch operation listed for your
   track: if any item fails, **nothing** changes. Show the state before
   and after a failed batch.
4. **Translation.** The loader reads records (from an
   `std::istringstream` standing in for a CSV file) using `std::stod` /
   `std::stoi`. Translate their `std::invalid_argument` /
   `std::out_of_range` into your `CorruptRecordError`, including the
   **line number** in the message. One bad line must not stop the
   others loading.
5. **A logging-and-rethrow** layer somewhere, using `throw;`.
6. **A `noexcept`-safe destructor**: your RAII class from Module 23 gets
   a `close()`/`stop()` that may throw, and a destructor that calls it
   inside `try`/`catch` so nothing ever escapes.
7. **Ordered handlers** in `main`: most specific first, your root class
   next, `std::exception` last.
8. **Guarantee comments.** Above every public member function of your
   main class, write which guarantee it gives: no-throw, strong, or
   basic.

## Track A — Generic: Course Enrolment

- **Hierarchy:** `SchoolError` → `CourseFullError` (carries the course
  title and capacity), `DuplicateEnrolmentError`, `PrerequisiteError`
  (carries the missing prerequisite), `StudentNotFoundError`,
  `CorruptRecordError`.
- **Batch (strong):** `Registrar::enrolMany(studentId, courseTitles)` —
  a student registers for several courses at once (e.g. "Robotics 2"
  needs "Robotics 1"); all or nothing.
- **Loader:** lines like `MP-014,Akua Owusu,13` (ID, name, age).

## Track B — Electrical/Electronic Engineering: Load Switching

- **Hierarchy:** `ElectricalError` → `OvercurrentError` (carries the
  circuit, the calculated current, and the breaker rating),
  `OvervoltageError`, `UnknownCircuitError`, `CorruptRecordError`.
- **Batch (strong):** `Panel::applySchedule(changes)` — switch several
  loads on or off across circuits at 18:00; if any circuit would exceed
  its breaker rating, **no** load is switched.
- **Loader:** lines like `kitchen,Kettle,2200` (circuit, load name,
  watts) on a 230 V supply.

## Track C — Biomedical Engineering: Medication Orders

- **Hierarchy:** `ClinicalError` → `DoseLimitError` (carries the drug,
  the requested daily total, and the maximum), `AllergyConflictError`
  (carries the allergen), `PatientNotFoundError`, `CorruptRecordError`.
- **Batch (strong):** `MedicationRecord::prescribeAll(patientId,
  orders)` — a ward round prescribes several drugs at once; if any one
  breaks a limit or conflicts with an allergy, **none** are added.
- **Loader:** lines like `CL-0007,Paracetamol,1000,4` (patient, drug,
  mg per dose, doses per day).

## Starter folders

- [`generic_starter/`](generic_starter/)
- [`ee_starter/`](ee_starter/)
- [`biomedical_starter/`](biomedical_starter/)

## When you're done

```bash
git add 31-exceptions-in-class-design
git commit -m "Complete Module 31 project: exception-safe core"
git push
```
