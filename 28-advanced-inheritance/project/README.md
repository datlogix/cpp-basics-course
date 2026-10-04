# Module 28 Project — A Real Diamond, Done Properly

Continue your track. Each track has a genuine case where one kind of
object really **is** two kinds of thing at once — which leads to a
diamond-shaped hierarchy. You'll build it correctly with virtual
inheritance, and use the rest of this module's tools along the way.

## Requirements (all tracks)

1. **The diamond.** Build the hierarchy shown for your track. The top
   class is a **virtual** base of both middle classes, and the bottom
   class constructs it directly. Print a trace line in the top class's
   constructor to *prove* it runs exactly once per bottom-class object.
2. **Polymorphism through every path.** Store a mix of all the concrete
   classes in a `std::vector<std::unique_ptr<TopClass>>` and print a
   report with one loop. Also pass the bottom-class object to a
   function taking each *middle* class by reference.
3. **`final`.** Mark the method and class named for your track as
   `final`, and add a comment showing the line that would now fail.
4. **Name hiding.** Your track's starter contains an overload that
   hides a base method. Show the compile error in a comment, then fix
   it with a `using`-declaration.
5. **Inheriting constructors.** Use `using Base::Base;` in at least one
   leaf class that adds behaviour but no new data.
6. **No slicing.** Add a comment at the one place in `main.cpp` where
   a by-value copy *would* slice, and show the correct alternative.
7. **Composition check.** In a comment at the top of your hierarchy
   header, answer: *"Could the bottom class have been designed with
   composition instead of multiple inheritance? What would be gained and
   lost?"*

## Track A — Generic: Teaching Researchers

```
                 Person               (virtual base: id, name)
                /      \
          Teacher      Researcher
                \      /
          TeachingResearcher           (teaches AND does research)
```

- `Teacher` has `monthlySalaryGhs()`, and `assign(std::string
  course)`.
- `Researcher` has a `grantGhs` and `publish(std::string title)`.
- `TeachingResearcher` gets a salary *plus* 10% of their grant per
  month.
- Also add `Principal final : public Teacher` (there is exactly one
  kind of principal; nobody derives from it), and make
  `Person::idCard()` → `final` in `Person` (a printed ID card format
  must be the same for everyone).
- **Name hiding:** `TeachingResearcher` adds
  `assign(std::string course, int periodsPerWeek)`, which hides
  `Teacher::assign(std::string)`.

## Track B — Electrical/Electronic Engineering: Smart Devices

```
                  Device              (virtual base: serial, location)
                 /      \
        PoweredDevice   NetworkedDevice
                 \      /
                 SmartPlug             (switches mains power AND is on Wi-Fi)
```

- `PoweredDevice` has `volts`, `watts`, and `emergencyShutdown()`.
- `NetworkedDevice` has an `ipAddress`, `signalStrengthDbm`, and
  `send(std::string message)`.
- `SmartPlug` reports its power use over the network.
- Make `PoweredDevice::emergencyShutdown()` `final` (safety-critical),
  and add a `final` leaf class `SmartMeter : public PoweredDevice,
  public NetworkedDevice` as a second bottom class.
- **Name hiding:** `SmartPlug` adds `send(double wattsReading)`, which
  hides `NetworkedDevice::send(std::string)`.

## Track C — Biomedical Engineering: Wearable Wireless Monitors

```
                MedicalDevice         (virtual base: serial, patient folder)
                 /         \
           Wearable      WirelessDevice
                 \         /
             SmartWatchMonitor         (worn by the patient AND transmits to the ward)
```

- `Wearable` has `batteryPercent` and `needsCharging()`.
- `WirelessDevice` has a `bluetoothId` and `transmit(std::string
  message)`.
- `SmartWatchMonitor` measures heart rate and transmits alerts.
- Make `MedicalDevice::alarm()` `final` (alarm behaviour is regulated
  and must be identical for every device), and add a `final` leaf class
  `WirelessEcgPatch : public Wearable, public WirelessDevice` as a
  second bottom class.
- **Name hiding:** `SmartWatchMonitor` adds `transmit(int heartRateBpm)`,
  which hides `WirelessDevice::transmit(std::string)`.

## Starter folders

- [`generic_starter/`](generic_starter/)
- [`ee_starter/`](ee_starter/)
- [`biomedical_starter/`](biomedical_starter/)

## When you're done

```bash
git add 28-advanced-inheritance
git commit -m "Complete Module 28 project: diamond hierarchy with virtual inheritance"
git push
```
