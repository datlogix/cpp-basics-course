# Module 22 — Multi-File Projects & Namespaces

Every program you've written so far lives in **one `.cpp` file**.
That's fine for 100 lines. It stops being fine somewhere around 500:
scrolling up and down to find a class, two people unable to edit the
program at the same time without conflicts, and recompiling *everything*
after a one-character change.

Real C++ projects are split across many files — usually one pair of
files per class. This module teaches you how that works:

- **header files** (`.h`) vs **source files** (`.cpp`)
- include guards and `#pragma once`
- compiling several files together, and what **compiling** vs
  **linking** actually means
- reading the two most common linker errors
- forward declarations
- **namespaces**, to stop names from colliding
- a first look at **CMake**, the build tool most C++ projects use

From this module on, every project in Part 3 is a multi-file project.

## Why split a program into files?

- **Organisation.** `student.h` tells you exactly where the `Student`
  class lives.
- **Faster builds.** Change one `.cpp` file and only that file has to
  be recompiled; the rest are reused.
- **Teamwork.** Two people can edit two different files without
  stepping on each other in Git.
- **Abstraction (Module 20!).** A header shows *what* a class offers.
  The source file hides *how*. Someone using your class only needs to
  read the header.

## Header files and source files

Module 21 showed that you can **declare** a method inside a class and
**define** it outside, with `ClassName::`. Multi-file projects take
that one step further: the declarations go in one file and the
definitions in another.

**`point.h` — the header (the "what")**:

```cpp
#pragma once

class Point {
private:
    double x;
    double y;

public:
    Point(double x, double y);
    double distanceTo(const Point& other) const;
    void print() const;
};
```

**`point.cpp` — the source file (the "how")**:

```cpp
#include "point.h"
#include <cmath>
#include <iostream>

Point::Point(double x, double y) : x(x), y(y) {}

double Point::distanceTo(const Point& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

void Point::print() const {
    std::cout << "(" << x << ", " << y << ")";
}
```

**`main.cpp` — the code that uses it**:

```cpp
#include "point.h"
#include <iostream>

int main() {
    Point a(0, 0);
    Point b(3, 4);
    std::cout << a.distanceTo(b) << std::endl;   // 5
    return 0;
}
```

Notice:

- `#include "point.h"` uses **quotes** for your own files, and
  `#include <iostream>` uses **angle brackets** for the standard
  library. Quotes tell the compiler to look in the current folder
  first.
- `point.cpp` includes its own header. That way, if the declaration in
  the header and the definition in the `.cpp` ever disagree, the
  compiler notices.
- `main.cpp` never sees the body of `distanceTo`. It only needs to know
  that the method *exists* and what it takes and returns.

### What goes where?

| In the header (`.h`) | In the source file (`.cpp`) |
|---|---|
| The class definition: members and method declarations | Method definitions (`Point::print() { ... }`) |
| Very short methods written inline, like simple getters (optional) | Definitions of `static` data members (`int Student::nextId = 1;`) |
| `#include`s the header itself needs (e.g. `<string>` if a member is a `std::string`) | `#include`s needed only by the method bodies (e.g. `<cmath>`, `<iostream>`) |
| Declarations of free functions | Definitions of free functions |

**Never** put `using namespace std;` in a header — it would silently
apply to every file that includes it (see "Namespaces" below).

## Include guards and `#pragma once`

`#include` is very simple: the preprocessor **pastes the whole file in**
at that spot. If `main.cpp` includes `student.h`, and also includes
`classroom.h` which *itself* includes `student.h`, then the `Student`
class ends up pasted in twice — and defining a class twice is a compile
error.

Every header must protect itself against being included twice. There
are two ways.

**`#pragma once`** — one line at the top of the header:

```cpp
#pragma once
// ... the rest of the header ...
```

**Classic include guards** — work everywhere, and you'll see them in a
lot of existing code:

```cpp
#ifndef POINT_H
#define POINT_H

// ... the rest of the header ...

#endif
```

The first time the file is included, `POINT_H` isn't defined, so the
contents are kept and `POINT_H` becomes defined. The second time, the
`#ifndef` check fails and the whole file is skipped.

`#pragma once` isn't technically part of the C++ standard, but every
mainstream compiler supports it. This course uses `#pragma once`;
recognise both.

## Building a multi-file program

The simplest way is to give `g++` every `.cpp` file at once:

```bash
g++ -std=c++17 -Wall -Wextra main.cpp point.cpp -o geometry
./geometry
```

Headers are **never** listed on the command line — they're pulled in
by `#include`.

### What actually happens: compiling, then linking

Building a C++ program is really two separate steps:

1. **Compiling.** Each `.cpp` file is compiled *on its own* into an
   **object file** (`.o`) of machine code. While compiling `main.cpp`,
   the compiler knows `distanceTo` *exists* (the header said so), but
   not where its code is. It leaves a note: "fill in the address of
   `Point::distanceTo` here later."
2. **Linking.** The **linker** combines all the object files into one
   program and fills in every one of those notes.

You can run the steps yourself to see this:

```bash
g++ -std=c++17 -Wall -Wextra -c point.cpp      # -> point.o
g++ -std=c++17 -Wall -Wextra -c main.cpp       # -> main.o
g++ point.o main.o -o geometry                 # link
```

`-c` means "compile only, don't link". If you now change only
`point.cpp`, you only need to re-run the first and last commands.
Build tools like CMake (below) track this for you automatically.

### The two linker errors you will definitely see

**`undefined reference to 'Point::distanceTo(...)'`** — something was
*declared* (so compiling succeeded) but the linker can't find its
*definition*. Usual causes:

- you forgot to list `point.cpp` on the command line;
- you misspelled the definition, or forgot `Point::` in front of it, so
  you defined an unrelated free function instead;
- the definition's signature doesn't match the declaration (a missing
  `const` counts!);
- you declared a `static` data member but never defined it in a `.cpp`.

**`multiple definition of 'helper()'`** — the *same* thing was defined
in more than one object file. Usual cause: you put a function's
**definition** (with a body) in a header that's included by two `.cpp`
files, so each of them got a copy. Fix: keep only the declaration in
the header and move the body into one `.cpp` file. (Methods written
*inside* a class body are allowed in headers — they're automatically
treated as `inline`, which tells the linker that duplicate copies are
expected and fine.)

Notice that these errors don't come with a line number in your code:
the compiler has already finished. When you see `undefined reference`
or `multiple definition`, think **linker**, and check your file list
and your definitions.

## Forward declarations

Sometimes a header only needs to know that a class **exists**, not
what's inside it — for example, when it only uses a pointer or
reference to it:

```cpp
// teacher.h
#pragma once
#include <string>

class Course;   // forward declaration: "there is a class called Course"

class Teacher {
private:
    std::string name;
    Course* currentCourse = nullptr;   // a pointer only - no need for the full class
public:
    void assign(Course& course);       // a reference only - also fine
};
```

The `.cpp` file that actually *uses* `Course`'s members then includes
`course.h` itself.

Forward declarations have two benefits: headers include fewer other
headers (so builds are faster), and they solve **circular includes**,
where `teacher.h` needs `Course` and `course.h` needs `Teacher`. If two
headers include each other, the include guards stop the infinite loop
but one class ends up used before it's defined. A forward declaration
in at least one of them breaks the cycle.

You **cannot** use a forward declaration when the compiler needs to
know the class's size or members: for a member held **by value**
(`Course course;`), as a base class, or to call one of its methods.

## Namespaces

As programs grow — and as you use other people's libraries — names
collide. Your project has a `Sensor` class; so does the library you
download. Which one does `Sensor` mean?

A **namespace** puts names inside a named scope:

```cpp
namespace makersplace {

class Student {
    // ...
};

void printWelcome();

}  // namespace makersplace
```

From outside the namespace you write the full name:

```cpp
makersplace::Student s("Akua");
makersplace::printWelcome();
```

You already know one namespace very well: `std`. That's what `std::`
in `std::cout` and `std::vector` means — "the `cout` that belongs to
the standard library".

Namespaces can be **nested**, and can be reopened across files: every
header and `.cpp` file in your project can wrap its contents in the
same `namespace makersplace { ... }` and they all add to one namespace.

```cpp
namespace makersplace::energy {     // C++17 nested namespace shorthand
    class Appliance { /* ... */ };
}

makersplace::energy::Appliance fan("Fan");
```

### `using` — and where *not* to use it

Typing full names gets long. `using` brings names into scope:

```cpp
using makersplace::Student;   // a using-declaration: just this one name
Student s("Akua");

using namespace makersplace;  // a using-directive: EVERY name in the namespace
```

`using namespace std;` is common in tutorials, but has a real cost: it
pulls in *hundreds* of names (`count`, `distance`, `max`, `size`, ...)
that can quietly clash with yours. Guidelines:

- **Never** put `using namespace` in a header.
- In a `.cpp` file, prefer `using` *declarations* for the few names you
  use a lot, or simply write `std::`.
- Inside a function body, a `using` only affects that function — the
  safest place for one.

## A first look at CMake

Typing `g++ main.cpp student.cpp classroom.cpp teacher.cpp ...` gets
tedious and error-prone — exactly the "forgot to list a file"
`undefined reference` mistake from above. **CMake** is the build tool
most C++ projects use. You describe your project once, in a file
called `CMakeLists.txt`, and CMake works out the commands.

A typical small project layout:

```
geometry/
  CMakeLists.txt
  include/
    point.h
  src/
    point.cpp
    main.cpp
```

`CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.16)
project(Geometry LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(geometry
    src/main.cpp
    src/point.cpp
)

target_include_directories(geometry PRIVATE include)
target_compile_options(geometry PRIVATE -Wall -Wextra)
```

- `add_executable` names the program and lists its `.cpp` files.
- `target_include_directories` tells the compiler where to find
  headers, so `#include "point.h"` works from `src/`.
- `target_compile_options` adds our usual warning flags.

To build (from inside the `geometry/` folder):

```bash
cmake -S . -B build        # configure: read CMakeLists.txt, write build files into build/
cmake --build build        # compile and link whatever has changed
./build/geometry           # run it
```

You run the first command once (and again whenever you edit
`CMakeLists.txt`). After that, `cmake --build build` is all you need,
and it only recompiles files that changed.

**Never commit the `build/` folder** — it's generated, machine-specific
output, just like compiled programs. Commit `CMakeLists.txt` and your
source files.

> **Installing CMake.** On Ubuntu/WSL: `sudo apt install cmake`. On
> macOS: `brew install cmake`. On Windows with MSYS2:
> `pacman -S mingw-w64-ucrt-x86_64-cmake`. Check it works with
> `cmake --version`. If you can't install it right now, every project
> in Part 3 can still be built with a plain `g++` command listing every
> `.cpp` file — the project READMEs show both.

## Common beginner mistakes

- Listing `.h` files on the `g++` command line, or forgetting to list a
  `.cpp` file (→ `undefined reference`).
- A header without `#pragma once` / include guards (→ "redefinition of
  class").
- Putting a non-inline function **definition** in a header that two
  `.cpp` files include (→ `multiple definition`).
- Forgetting `ClassName::` in front of a method definition in the
  `.cpp` file — it compiles as an unrelated free function, then fails
  with `undefined reference` (or complains it can't see private
  members).
- A `.cpp` file that doesn't include its own header.
- `using namespace std;` in a header.
- Two headers that include each other — break the cycle with a forward
  declaration.
- Committing the `build/` folder to Git.

## Try it yourself

1. Work through [`examples/`](examples/). Each example in this module
   is a **folder**; its comments explain how to build it.
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md), continuing your
   track.
4. Commit:

   ```bash
   git add 22-multi-file-projects
   git commit -m "Complete Module 22: multi-file projects and namespaces"
   git push
   ```

Next: **[Module 23 — Object Lifetime, Destructors & RAII](../23-object-lifetime-raii/README.md)**.
