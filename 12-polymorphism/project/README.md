# Module 12 Project — A Polymorphic Collection

Pick **one** track. All three reuse Module 11's hierarchy and add the
payoff: a `vector` of base-class pointers, looped over once, correctly
calling each object's own overridden method.

## Track A — Generic: Shape Collection

1. Reuse (or rebuild) the `Shape` hierarchy from Module 11's project,
   but make `area()` and a virtual destructor `virtual`, and mark each
   derived `area()` with `override`.
2. Build a `std::vector<Shape*>` containing at least one `Circle` and
   one `Rectangle`, created with `new`.
3. Loop over the vector, printing each shape's area.
4. Compute and print the **total area** of all shapes combined.
5. `delete` every pointer before the program ends.

## Track B — Electrical/Electronic Engineering: Circuit Impedance Calculator

1. Reuse (or rebuild) the `Component` hierarchy from Module 11, making
   `describe()` and the destructor `virtual`.
2. Add a virtual method `double impedance(double frequencyHz)` to
   `Component` (default: return `0`), overridden by each derived class
   with a simplified formula:
   - Resistor: impedance = resistance (frequency-independent)
   - Capacitor: impedance = `1.0 / (2 * PI * frequencyHz * capacitance)`
   - Inductor: impedance = `2 * PI * frequencyHz * inductance`
3. Build a `std::vector<Component*>` with one of each.
4. Loop over the vector at a given frequency (e.g. `60` Hz), printing
   each component's impedance, and print the **sum** as the circuit's
   total series impedance.
5. `delete` every pointer before the program ends.

## Track C — Biomedical Engineering: Unified Patient Monitor

1. Reuse (or rebuild) the `MedicalDevice` hierarchy from Module 11,
   making `printHeader()`/`printReading()` and the destructor `virtual`.
2. Add a third derived class `ECGMonitor` with an `int heartRateBpm`
   and its own `printReading()`.
3. Build a `std::vector<MedicalDevice*>` with one of each device.
4. Loop over the vector once, calling `printReading()` on each — this
   is your unified patient dashboard, printed with a single loop
   regardless of device type.
5. `delete` every pointer before the program ends.

## Starter files

- [`generic_starter.cpp`](generic_starter.cpp)
- [`ee_starter.cpp`](ee_starter.cpp)
- [`biomedical_starter.cpp`](biomedical_starter.cpp)

## When you're done

```bash
g++ <your_chosen_starter>.cpp -o polymorphism_project
./polymorphism_project
```

```bash
git add 12-polymorphism
git commit -m "Complete Module 12 project: polymorphic collection"
git push
```
