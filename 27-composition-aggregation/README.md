# Module 27 — Composition, Aggregation & Association

Module 11 introduced one relationship between classes: **inheritance**,
"is-a". It's the relationship beginners reach for first — and overuse
most. In real designs, most classes are related in a different way:
one object **has**, **contains**, **uses**, or **knows about** another.

Module 26 gave you the tools to express *ownership* precisely
(`unique_ptr`, `shared_ptr`, `weak_ptr`, references, raw borrowing
pointers). This module gives you the *design vocabulary* to decide
which relationship you actually mean, and maps each one to code:

- **composition** — a whole made of parts that live and die with it
- **aggregation** — a whole that groups parts which exist on their own
- **association** — two objects that know about each other
- **dependency** — one object briefly uses another
- **composition over inheritance** — why "has-a" is usually better
  than "is-a" for reusing behaviour
- **delegation** — forwarding work to a part
- drawing all of these in **UML**

## "is-a" vs "has-a"

Before writing `class A : public B`, say the relationship out loud:

- "A `TextBook` **is a** `Book`." ✔ — inheritance makes sense.
- "A `Car` **is an** `Engine`." ✘ — nonsense. "A `Car` **has an**
  `Engine`." ✔
- "A `Robot` **is a** `Motor`." ✘ — "A `Robot` **has** motors." ✔

If "is-a" sounds wrong, inheritance is wrong, even if it would let you
reuse some code. Every relationship in this module is some kind of
**has-a** or **knows-about**.

## Composition — "is made of"

**Composition** is the strongest has-a relationship:

- the **whole** owns the **part**;
- the part is created with the whole and **destroyed with the whole**;
- a part belongs to **exactly one** whole at a time;
- the part makes little sense on its own *in this program*.

Examples: a `Robot` is composed of its `Chassis`, `Motor`s and
`Battery`; a `Patient`'s record is composed of `VitalSigns` entries; a
`House` is composed of `Room`s.

**In C++**, composition is usually a **member held by value**:

```cpp
class Battery {
    double chargePercent = 100;
public:
    void drain(double amount);
    double level() const;
};

class Robot {
private:
    Battery battery;              // composition: part of the Robot itself
    Motor leftMotor;
    Motor rightMotor;
public:
    void drive(int seconds) {
        leftMotor.run(seconds);
        rightMotor.run(seconds);
        battery.drain(seconds * 0.5);
    }
};
```

When a `Robot` is created, its battery and motors are created (Module
23's construction order); when it's destroyed, they're destroyed. No
pointers, no `new`, no destructor to write.

When a part must be **polymorphic**, or **optional**, or **too large to
hold directly**, composition uses a `std::unique_ptr` member instead —
still sole, lifetime-bound ownership:

```cpp
class Robot {
private:
    std::unique_ptr<Sensor> frontSensor;   // still composition: Robot owns it alone
};
```

[`examples/01_composition.cpp`](examples/01_composition.cpp) traces a
robot and its parts being created and destroyed together.

## Aggregation — "groups together"

**Aggregation** is a weaker has-a:

- the whole **groups** or **uses** the parts, but does **not** control
  their lifetime;
- the parts exist **independently** — before, after, and apart from
  the whole;
- a part may belong to **several** wholes at once.

Examples: a `Club` aggregates `Student`s (deleting the club doesn't
delete the students); a `Department` aggregates `Teacher`s; a
`Playlist` aggregates `Song`s.

**In C++**, aggregation is a member that **doesn't own** what it
points to: a raw pointer, a reference, or a `std::weak_ptr` (when the
parts are managed by `shared_ptr`):

```cpp
class Club {
private:
    std::string name;
    std::vector<Student*> members;   // aggregation: the club doesn't own students
public:
    void join(Student& s) { members.push_back(&s); }
};
```

Something *else* owns the students — a `School`, or `main`. The
critical rule, which Module 26 called *borrowing*: **the parts must
outlive the whole's use of them**. A `Club` holding a raw pointer to a
`Student` who has been destroyed holds a dangling pointer. If you can't
guarantee the lifetimes, use `shared_ptr` + `weak_ptr`, as you did in
Module 26's project, so the whole can *detect* that a part has gone.

[`examples/02_aggregation.cpp`](examples/02_aggregation.cpp) shows a
department and its teachers, where destroying the department leaves
the teachers untouched.

### Composition or aggregation? Ask about lifetime

The quickest test: **"If I destroy the whole, should the part be
destroyed too?"**

| Question | Composition | Aggregation |
|---|---|---|
| Whole destroyed → part destroyed? | Yes | No |
| Can the part belong to several wholes? | No | Yes |
| Can the part exist before the whole? | Not really | Yes |
| Typical C++ member | value, or `std::unique_ptr` | `T*`, `T&`, `std::weak_ptr`, or a `std::shared_ptr` shared with others |

## Association — "knows about"

**Association** is any longer-term relationship where one object
**refers to** another, without "whole" and "part" — they're peers. A
`Doctor` is associated with their `Patient`s; a `Teacher` with the
`Course` they teach; a `Bus` with its `Driver`.

Associations can be:

- **one-way** (only one side knows): a `Ticket` knows its `Bus`, but
  the `Bus` doesn't keep a list of tickets;
- **two-way** (both sides know): a `Doctor` knows their patients *and*
  each `Patient` knows their doctor.

**In C++**, association is the same non-owning pointer, reference or
`weak_ptr` member as aggregation; the difference is in the *meaning*
(peers, not a whole and its parts). Two-way associations need care:
both sides must be kept **consistent**. If a patient changes doctor,
the old doctor's list and the new doctor's list must both be updated —
so do it in **one** method that updates both sides, never by setting
each side separately from outside.

[`examples/03_association.cpp`](examples/03_association.cpp) keeps a
two-way doctor–patient association consistent. (It uses Module 22's
forward declarations, because each class refers to the other.)

## Dependency — "uses, briefly"

The weakest relationship. A class **depends on** another when it uses
it **temporarily** — typically as a function parameter or a local
variable — and keeps no member referring to it afterwards:

```cpp
class ReportPrinter {
public:
    void print(const Gradebook& book) const;   // depends on Gradebook - holds no reference after
};
```

Dependencies are the least "sticky" relationship, which makes them
the easiest to change later. If a class only needs something for one
method, pass it as a parameter rather than storing it as a member.

## Drawing relationships in UML

Module 20 introduced UML boxes and the inheritance arrow. Here are the
others, in the text style we've been using:

```
 Robot ◆────── Battery        composition   (filled diamond at the WHOLE)
 Club  ◇────── Student        aggregation   (hollow diamond at the WHOLE)
 Doctor ────── Patient        association   (plain line; an arrowhead shows a one-way association)
 ReportPrinter - - - -> Gradebook   dependency  (dashed arrow: "uses")
 TextBook ─────▷ Book          inheritance   (hollow triangle at the BASE)
```

In plain ASCII (when you can't type ◆, ◇ and ▷), many people write
`<*>---` for composition, `<>---` for aggregation, `- - ->` for a
dependency, and `----|>` for inheritance.

You can add **multiplicity** at each end: `1`, `0..1`, `*` (any
number), `1..*` (at least one):

```
 Robot <*>--------- 2 Motor          a Robot has exactly 2 Motors
 Club  <>--------- * Student          a Club has any number of Students
 Doctor 1 --------- * Patient         one doctor, many patients
```

## Composition over inheritance

Here is a design that compiles and "reuses code":

```cpp
class SensorLog : public std::vector<double> {   // "a SensorLog IS-A vector"?
public:
    double average() const;
};
```

It looks convenient — `SensorLog` gets `push_back`, `size`, and
everything else for free. But now *everyone* can call *every* vector
operation on a `SensorLog`: `erase` the middle, `clear` it, insert
nonsense, sort it... Any rule the log wanted to enforce (e.g. "readings
must be between -40 and 125 °C") can be bypassed. You've inherited the
vector's entire **interface**, not just its storage. And "a sensor log
**is a** vector" is a statement about implementation, not meaning.

With composition:

```cpp
class SensorLog {
private:
    std::vector<double> readings;   // HAS-A vector
public:
    bool add(double celsius) {      // the only way in - and it validates
        if (celsius < -40 || celsius > 125) return false;
        readings.push_back(celsius);
        return true;
    }
    double average() const;
    int size() const { return static_cast<int>(readings.size()); }
};
```

`SensorLog` exposes exactly what it means to expose, and keeps its
invariant (Module 21). This is the guideline:

> **Prefer composition over inheritance** for reusing behaviour. Use
> inheritance when there is a genuine "is-a" relationship *and* you
> need polymorphism (code that works through a base pointer or
> reference to any derived type).

### The "class explosion" problem

Inheritance also breaks down when features combine. Suppose robots can
have a `Camera`, a `Gripper`, and `Wheels` or `Legs`. Modelling that
with inheritance:

```
Robot
 ├── WheeledRobot
 │    ├── WheeledRobotWithCamera
 │    ├── WheeledRobotWithGripper
 │    └── WheeledRobotWithCameraAndGripper
 └── LeggedRobot
      ├── LeggedRobotWithCamera
      ├── ...
```

Every new feature *doubles* the number of classes. With composition,
a robot simply **has** whichever parts it has:

```cpp
class Robot {
private:
    std::unique_ptr<Locomotion> locomotion;   // Wheels or Legs (polymorphic)
    std::unique_ptr<Camera> camera;           // may be nullptr: no camera
    std::unique_ptr<Gripper> gripper;         // may be nullptr: no gripper
};
```

One `Robot` class, any combination, and the parts can even be changed
at runtime. [`examples/04_composition_over_inheritance.cpp`](examples/04_composition_over_inheritance.cpp)
contrasts both `SensorLog` designs and builds a configurable robot.

## Delegation

When a whole receives a request that one of its parts knows how to
handle, it **delegates** — forwards the call:

```cpp
class Robot {
private:
    Battery battery;
public:
    double batteryLevel() const { return battery.level(); }   // delegation
};
```

Delegation is how composition "reuses" behaviour: instead of
inheriting `level()` from `Battery`, `Robot` offers its own
`batteryLevel()` and passes the work on. The difference is control:
`Robot` chooses exactly which of the battery's abilities to expose, and
can add rules around them.

## Common beginner mistakes

- Using inheritance for "has-a" (`class Car : public Engine`), just to
  reuse methods.
- Inheriting from a standard container (`class X : public std::vector<...>`)
  instead of having one as a member.
- Holding a part by raw pointer and calling it composition — if the
  whole owns it, use a value member or `std::unique_ptr` so the
  ownership is visible and automatic.
- Aggregation through a raw pointer to a part that can be destroyed
  first (a dangling pointer). Make sure parts outlive the whole, or use
  `shared_ptr`/`weak_ptr` so the whole can tell.
- Updating only one side of a two-way association.
- Storing a member for something used in just one method — make it a
  parameter (a dependency) instead.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md), continuing your
   track.
4. Commit:

   ```bash
   git add 27-composition-aggregation
   git commit -m "Complete Module 27: composition, aggregation and association"
   git push
   ```

Next: **[Module 28 — Advanced Inheritance](../28-advanced-inheritance/README.md)**.
