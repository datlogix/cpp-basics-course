# Module 29 Project — Program to Interfaces

Continue your track. In this project you'll build a small framework:
an **abstract base class** that fixes a common procedure, several
**concrete classes** that fill in the details, and **interfaces** that
let the rest of the program work with *capabilities* instead of
concrete types.

## Requirements (all tracks)

1. **An abstract base class with a Template Method.** Its public,
   non-virtual method runs a fixed sequence of steps, some of which are
   `protected` pure virtual functions supplied by each concrete class.
2. **At least three concrete classes**, each overriding every pure
   virtual function. Show (in a comment) the compile error you get when
   one is missing.
3. **Two interfaces** (pure virtual functions only, no data, virtual
   `= default` destructor). Your concrete classes implement one or both.
   At least one class in your program implements an interface **without**
   being part of the abstract hierarchy.
4. **Functions that depend only on an interface** — they must not
   mention any concrete class. Pass them a mixed collection.
5. **`clone()`** returning `std::unique_ptr<Base>`, used for the
   scenario described for your track.
6. **RTTI, used responsibly.** Either use `dynamic_cast` once, for a
   genuine "does this object have this capability?" question (with a
   comment justifying it), *or* write a comment explaining why your
   design never needed it.
7. **Vtable diagram.** In a comment at the top of `main.cpp`, draw the
   vtable of one of your concrete classes (as in the README).
8. **No virtual calls from constructors or destructors.**

## Track A — Generic: Assessments and Report Cards

- **Abstract base:** `Assessment` with a Template Method
  `std::string gradeLine() const` that computes a percentage from the
  pure virtual `rawScore()` and `maxScore()`, applies the pure virtual
  `weight()`, and formats a line.
- **Concrete:** `Exam`, `Coursework` (average of several assignments),
  and `RoboticsProject` (a rubric: design, build, code, presentation,
  each out of 25).
- **Interfaces:** `Gradable` (`double percentage() const`) and
  `Reportable` (`std::string reportLine() const`). An `Attendance`
  record (not an assessment) is also `Reportable`.
- **Functions:** `void printReportCard(const std::vector<const Reportable*>&)`
  and `double weightedAverage(const std::vector<const Gradable*>&)`.
- **`clone()`:** a student who resits an exam gets a *copy* of the
  original exam object with a new score; the original stays on record.

## Track B — Electrical/Electronic Engineering: Sensor Framework

- **Abstract base:** `Sensor` with a Template Method `Reading sample()`
  that calls the pure virtual `readRaw()` (an ADC count 0–1023),
  converts it with the pure virtual `convert(int raw)`, and checks it
  with the pure virtual `inRange(double)`.
- **Concrete:** `Thermistor` (temperature in °C), `CurrentSensor`
  (amps), and `LightSensor` (lux).
- **Interfaces:** `Calibratable` (`void calibrate(double offset)`) and
  `Alarmable` (`bool inAlarm() const`, `std::string alarmMessage()
  const`). A `CircuitBreaker` (not a sensor) is also `Alarmable` (when
  tripped).
- **Functions:** `void alarmPanel(const std::vector<const Alarmable*>&)`
  and `void calibrateAll(const std::vector<Calibratable*>&, double)`.
- **`clone()`:** when a sensor fails, the technician clones its
  configuration onto a replacement unit with a new serial number.

## Track C — Biomedical Engineering: Vital-Sign Monitoring

- **Abstract base:** `VitalSignMonitor` with a Template Method
  `void check()` that calls the pure virtual `measure()`, classifies
  the value with the pure virtual `classify(double)` (returning
  `"normal"`, `"warning"` or `"critical"`), and records the result.
- **Concrete:** `HeartRateMonitor`, `SpO2Monitor`, and
  `TemperatureMonitor`.
- **Interfaces:** `Alarmable` (`bool inAlarm() const`, `std::string
  alarmMessage() const`) and `Chartable` (`std::string chartEntry()
  const`). A `FluidBalanceRecord` (not a monitor) is also `Chartable`.
- **Functions:** `void nurseStation(const std::vector<const Alarmable*>&)`
  and `void printChart(const std::vector<const Chartable*>&)`.
- **`clone()`:** when a new patient is admitted to a bed, the nurse
  clones the previous bed's monitor configuration (thresholds) for the
  new patient.

## Starter folders

- [`generic_starter/`](generic_starter/)
- [`ee_starter/`](ee_starter/)
- [`biomedical_starter/`](biomedical_starter/)

## When you're done

```bash
git add 29-abstract-classes-interfaces
git commit -m "Complete Module 29 project: abstract classes and interfaces"
git push
```
