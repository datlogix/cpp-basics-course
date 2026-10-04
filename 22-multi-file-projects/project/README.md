# Module 22 Project — Turn Your Track Into a Real Multi-File Project

Continue your track. Until now your track's code has lived in a single
`.cpp` file. In this project you'll reorganise it into the layout real
C++ projects use — and that every remaining module in Part 3 (and
Capstone Project 3) will build on:

```
<track>_starter/
  CMakeLists.txt
  include/        <- one header per class
  src/            <- one .cpp per class, plus main.cpp
```

Each starter folder already contains **one class fully split for you**
as a model to copy, and a **second class for you to split yourself**.

## Requirements (all tracks)

1. Study the model class's `.h` and `.cpp` pair. Notice the
   `#pragma once`, the namespace, what's in the header vs the source
   file, and which `#include`s are in which file.
2. Move your second class (from your Module 20/21 work) into its own
   `include/<class>.h` and `src/<class>.cpp`, following the model
   exactly. Every method body goes in the `.cpp` file except one-line
   getters, which you may keep inline in the header.
3. Wrap **everything** in your track's namespace (see below). No
   `using namespace` in any header.
4. Use a **forward declaration** wherever a header only needs a
   reference or pointer to another class.
5. Add the new `.cpp` file to `add_executable` in `CMakeLists.txt`.
6. Build it **both** ways and make sure both produce zero warnings:

   ```bash
   # With CMake (from inside your <track>_starter folder):
   cmake -S . -B build
   cmake --build build
   ./build/<program name>

   # Without CMake:
   g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o program
   ./program
   ```

7. Write a short comment at the top of `main.cpp` answering: *"If I
   change only `src/<your class>.cpp`, which files does CMake recompile,
   and why?"*

## Track A — Generic: School Club Registry

Namespace: `makersplace::school`. The model class is `Student`. You
split `Club` (`include/club.h`, `src/club.cpp`). `Club` stores
`Student` objects by value, so `club.h` must `#include "student.h"` —
a forward declaration isn't enough there. Explain why in a comment.

## Track B — Electrical/Electronic Engineering: Home Energy Monitor

Namespace: `makersplace::energy`. The model class is `Appliance`. You
split `Room` (`include/room.h`, `src/room.cpp`), which holds a
`std::vector<Appliance>` and calculates its daily kWh and monthly cost.
Also move the shared constant `DAYS_PER_MONTH` into a small header
`include/energy_constants.h` (inside the namespace), declared as
`const int DAYS_PER_MONTH = 30;`. Both `appliance.cpp` and `room.cpp`
then include it. A `const` variable like this is allowed in a header
included by several `.cpp` files — each file gets its own private copy
— whereas a *function* with a body would cause a `multiple definition`
error. Add a comment in the header saying so.

## Track C — Biomedical Engineering: Clinic Appointment System

Namespace: `makersplace::clinic`. The model class is `Patient`. You
split `Doctor` (`include/doctor.h`, `src/doctor.cpp`). A doctor's
appointment only needs to *refer* to a patient — store the patient's
folder number (a `std::string`), and take `const Patient&` as a
parameter in `book(...)`. That means `doctor.h` can use a **forward
declaration** of `Patient`, and only `doctor.cpp` includes
`patient.h`.

## Starter folders

- [`generic_starter/`](generic_starter/)
- [`ee_starter/`](ee_starter/)
- [`biomedical_starter/`](biomedical_starter/)

## When you're done

Do **not** commit the `build/` folder (the repository's `.gitignore`
already ignores it).

```bash
git add 22-multi-file-projects
git commit -m "Complete Module 22 project: multi-file CMake project"
git push
```
