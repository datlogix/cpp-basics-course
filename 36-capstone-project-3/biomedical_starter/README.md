# Hospital Ward Patient Monitoring System

> **TODO (Stage 4):** replace this file with your own README: what the
> system does, how to build it, how to run the demo and the tests, and
> links to `DESIGN.md`, `PATTERNS.md`, `TESTING.md` and `REFLECTION.md`.

## Build and run

```bash
cmake -S . -B build
cmake --build build
./build/app            # the menu
./build/app --demo     # the scripted demo scenario
ctest --test-dir build --output-on-failure
```

## Starter contents

| File | What it gives you |
|---|---|
| `include/errors.h` | The root of your exception hierarchy, and `CorruptRecordError` |
| `include/repository.h` | The `HasId` concept and a `Repository<T>` skeleton |
| `include/statistics.h` | A `Numeric`-constrained `Statistics<T>` skeleton |
| `include/medical_device.h`, `src/medical_device.cpp` | The abstract base of your main hierarchy |
| `include/events.h` | The Observer interface for your system's events |
| `include/dose.h`, `src/dose.cpp` | Your value type, with its first operators |
| `src/main.cpp` | The menu and `--demo` skeleton |
| `tests/minitest.h`, `tests/test_main.cpp` | The test framework from Module 35 and a first test |

Everything else — and every one of these files — is yours to change.
Start with `DESIGN.md`.
