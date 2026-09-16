# Module 11 Project — A Class Hierarchy

Pick **one** track. All three practice the same skill: a base class with
shared data/behavior, and two or more derived classes that each add
their own fields and their own version of a shared method.

## Track A — Generic: Shape Hierarchy

1. Base class `Shape` with a protected `std::string name` and a
   constructor setting it.
2. Derived class `Circle : public Shape` adding `double radius`, its own
   constructor, and a method `double area()`.
3. Derived class `Rectangle : public Shape` adding `double length` and
   `double width`, its own constructor, and a method `double area()`.
4. In `main`, create one of each and print `"<name>: area = <area>"` for
   both.

## Track B — Electrical/Electronic Engineering: Circuit Component Hierarchy

1. Base class `Component` with protected `std::string name` and
   `double value`, a constructor setting both, and a method
   `void describe()` printing them.
2. Derived class `Resistor : public Component` — no extra fields needed;
   override `describe()` to print the value with the unit "ohms".
3. Derived class `Capacitor : public Component` — override `describe()`
   to print the value with the unit "farads".
4. Derived class `Inductor : public Component` — override `describe()`
   to print the value with the unit "henries".
5. In `main`, create one of each and call `describe()` on all three.

## Track C — Biomedical Engineering: Medical Device Hierarchy

1. Base class `MedicalDevice` with protected `std::string deviceId` and
   `std::string patientName`, a constructor setting both, and a method
   `void printHeader()` printing `"[<deviceId>] Patient: <patientName>"`.
2. Derived class `Thermometer : public MedicalDevice` adding
   `double temperatureCelsius` and a method `void printReading()`
   that calls `printHeader()` then prints the temperature.
3. Derived class `PulseOximeter : public MedicalDevice` adding
   `int oxygenSaturationPercent` and its own `printReading()`.
4. In `main`, create one of each and call `printReading()` on both.

## Starter files

- [`generic_starter.cpp`](generic_starter.cpp)
- [`ee_starter.cpp`](ee_starter.cpp)
- [`biomedical_starter.cpp`](biomedical_starter.cpp)

## When you're done

```bash
g++ <your_chosen_starter>.cpp -o hierarchy_project
./hierarchy_project
```

```bash
git add 11-inheritance
git commit -m "Complete Module 11 project: class hierarchy"
git push
```
