# Module 13 Project — A Class With Natural Arithmetic

Pick **one** track. All three overload `+`, a comparison, and `<<` for a
class that genuinely behaves like a number in its domain.

## Track A — Generic: Vector2D

1. Build a class `Vector2D` with private `double x, y` and a constructor.
2. Overload `operator+` (component-wise addition).
3. Overload `operator==` (both components equal).
4. Overload `operator<<` as a friend free function, printing
   `"(x, y)"`.
5. In `main`, create two vectors, print their sum, and check equality.

## Track B — Electrical/Electronic Engineering: Complex Impedance

AC circuit impedance is complex-number arithmetic — a natural real-world
use of everything this module teaches.

1. Build a class `Complex` with private `double real, imag` and a
   constructor.
2. Overload `operator+` and `operator-` (add/subtract two impedances,
   e.g. combining series impedances).
3. Overload `operator*` — complex multiplication:
   `(a+bi)(c+di) = (ac - bd) + (ad + bc)i`.
4. Overload `operator<<` as a friend free function, printing
   `"a + bi"` (or `"a - bi"` when `imag` is negative — optional polish).
5. In `main`, create two `Complex` impedances (e.g. a resistor's
   `(50, 0)` and a capacitor's `(0, -30)`), print their series sum
   `Z_total = Z1 + Z2`.

## Track C — Biomedical Engineering: Dosage

1. Build a class `Dosage` with private `double milligrams` and a
   constructor.
2. Overload `operator+` (combine two doses given in one sitting).
3. Overload `operator*` taking a `double` scale factor (e.g. scaling a
   per-kg dose by a patient's weight): `Dosage operator*(double factor) const`.
4. Overload `operator<` comparing `milligrams`, useful for checking
   against a maximum safe dose.
5. Overload `operator<<` as a friend free function, printing
   `"<mg> mg"`.
6. In `main`, compute a patient's total dose from two administrations,
   scale a per-kg dose by a patient weight, and check it against a
   `const Dosage MAX_SAFE_DOSE` using your overloaded `<`.

## Starter files

- [`generic_starter.cpp`](generic_starter.cpp)
- [`ee_starter.cpp`](ee_starter.cpp)
- [`biomedical_starter.cpp`](biomedical_starter.cpp)

## When you're done

```bash
g++ <your_chosen_starter>.cpp -o operator_project
./operator_project
```

```bash
git add 13-operator-overloading
git commit -m "Complete Module 13 project: operator overloading"
git push
```
