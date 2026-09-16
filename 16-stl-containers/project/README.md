# Module 16 Project — A Keyed Database

Pick **one** track. All three build a small `map`-based database keyed
by name/ID, holding a history of values per key, with a flagging rule
applied while iterating.

## Track A — Generic: Inventory Tracker

1. Build a `std::map<std::string, int>` mapping item name to quantity in
   stock.
2. Let the user add items (name + starting quantity), restock an
   existing item (increase its quantity), or sell an item (decrease its
   quantity, never below 0).
3. Print the full inventory (sorted by name, automatically, since it's
   a `map`).
4. Print every item with a quantity below a restock threshold (e.g. `5`).

## Track B — Electrical/Electronic Engineering: Component Inventory

1. Build a `std::map<std::string, std::vector<double>>` mapping a
   circuit node name (e.g. `"N1"`) to a history of voltage samples taken
   at that node.
2. Let the user add a sample to a named node (creating the node's entry
   automatically the first time).
3. Print, for every node, its sample count and average voltage.
4. Print every node whose **most recent** sample exceeds a
   `const double OVER_VOLTAGE_THRESHOLD` (e.g. `4.5` V).

## Track C — Biomedical Engineering: Patient Database

1. Build a `std::map<std::string, std::vector<double>>` mapping a
   patient ID to a history of heart-rate readings for that patient.
2. Let the user add a reading for a named patient ID (creating the
   patient's entry automatically the first time).
3. Print, for every patient, their reading count and average heart rate.
4. Print every patient whose **most recent** reading falls outside the
   normal resting range (`60`–`100` bpm), flagged for review.

## Starter files

- [`generic_starter.cpp`](generic_starter.cpp)
- [`ee_starter.cpp`](ee_starter.cpp)
- [`biomedical_starter.cpp`](biomedical_starter.cpp)

## When you're done

```bash
g++ <your_chosen_starter>.cpp -o database_project
./database_project
```

```bash
git add 16-stl-containers
git commit -m "Complete Module 16 project: keyed database"
git push
```
