# Module 14 — File I/O

Every program you've written so far forgets everything the moment it
closes. This module fixes that: **file I/O** lets a program write data
that survives after it exits, and read it back in on a later run — the
difference between a calculator and a program with actual persistent
records.

## The core idea: files are just another stream

You already know `std::cout` (write to the screen) and `std::cin` (read
from the keyboard) — both are **streams**. A file stream works exactly
the same way, using `<<` and `>>` exactly as before, just connected to a
file instead of the console.

```cpp
#include <fstream>
```

## Writing to a file

```cpp
#include <fstream>
#include <iostream>

int main() {
    std::ofstream outFile("readings.txt"); // "o" = output

    if (!outFile) {
        std::cout << "Could not open file for writing." << std::endl;
        return 1;
    }

    outFile << "23.5" << std::endl;
    outFile << "24.1" << std::endl;
    outFile << "22.8" << std::endl;

    outFile.close();  // flush and release the file
    return 0;
}
```

- `std::ofstream` ("output file stream") opens a file for **writing**.
  If the file doesn't exist, it's created; if it does, its contents are
  **overwritten** by default.
- `outFile << value` works exactly like `std::cout << value`.
- `if (!outFile)` checks whether the file actually opened successfully
  (e.g. it fails if the folder doesn't exist or you lack permission) —
  always check this before writing or reading; a silent failure here
  produces confusing bugs much later.
- `.close()` — always close a file when you're done with it. This
  ensures everything is actually written to disk (data can otherwise sit
  in a memory buffer) and frees the underlying OS resource.

## Reading from a file

```cpp
#include <fstream>
#include <iostream>

int main() {
    std::ifstream inFile("readings.txt"); // "i" = input

    if (!inFile) {
        std::cout << "Could not open file for reading." << std::endl;
        return 1;
    }

    double reading;
    while (inFile >> reading) {
        std::cout << "Read: " << reading << std::endl;
    }

    inFile.close();
    return 0;
}
```

- `std::ifstream` ("input file stream") opens a file for **reading**.
- `while (inFile >> reading)` is the standard idiom for "keep reading
  values until there's nothing left." `inFile >> reading` returns the
  stream itself, and a stream evaluates as `false` once it hits the end
  of the file (or a read error) — so the loop naturally stops exactly
  when the file runs out, with no need to know the line count in
  advance.

## Reading line by line with `getline`

For text that isn't just single whitespace-separated values (e.g. a
patient's full name, or a CSV row), use `std::getline` — exactly the
function from Module 3, just now reading from a file stream instead of
`std::cin`:

```cpp
std::ifstream inFile("patients.txt");
std::string line;
while (std::getline(inFile, line)) {
    std::cout << "Line: " << line << std::endl;
}
```

## Appending instead of overwriting

By default, `std::ofstream` **erases** the file's previous contents.
To add new data to the *end* of an existing file instead — essential for
a log that should accumulate across many program runs — pass the
`std::ios::app` flag:

```cpp
std::ofstream logFile("session_log.txt", std::ios::app);
logFile << "New session started." << std::endl;
```

## A simple CSV pattern

Comma-separated values (CSV) is the simplest common structured file
format — one record per line, fields separated by commas. Writing it is
just careful use of `<<`:

```cpp
outFile << timestamp << "," << voltage << "," << current << std::endl;
```

Reading it back requires a bit more care — read the whole line, then
split it on commas (`std::getline` with a custom delimiter is one
clean way):

```cpp
std::string line;
while (std::getline(inFile, line)) {
    std::stringstream ss(line);   // treat the line itself as a stream
    std::string field;
    while (std::getline(ss, field, ',')) {
        std::cout << field << " | ";
    }
    std::cout << std::endl;
}
```

`std::stringstream` (from `<sstream>`) lets you re-use the exact same
`>>`/`getline` tools on a string in memory as if it were a file — a
handy trick worth recognizing even though this course only needs the
pattern shown above.

## Converting a text field back into a number

Every field read with `getline` (including from a CSV split like above)
is a `std::string` — even a field that "looks like" a number. To use it
as one, convert explicitly:

```cpp
std::string scoreText = "87.5";
double score = std::stod(scoreText);   // "string to double"
int count = std::stoi("42");            // "string to int"
```

`std::stod`/`std::stoi` throw an exception (Module 15 covers exactly
what that means and how to handle it) if the text isn't actually a
valid number — worth knowing now, even before that module formalizes it.

## Common beginner mistakes

- Forgetting to `#include <fstream>`.
- Not checking `if (!file)` before using it, then being confused by
  silently-missing data when the file simply never opened.
- Opening for writing (`ofstream`) without realizing it erases existing
  content — use `std::ios::app` when you mean to append.
- Forgetting `.close()` — usually harmless for a short program (the
  destructor closes it automatically when the stream variable goes out
  of scope), but an explicit habit worth building for larger programs
  where a file might stay open much longer than intended.
- Mixing up `ifstream` (read) and `ofstream` (write) — the "i"/"o"
  prefix names spell out the direction, matching `cin`/`cout`.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — pick the Generic,
   EE, or Biomedical track.
4. Commit:

   ```bash
   git add 14-file-io
   git commit -m "Complete Module 14: file I/O"
   git push
   ```

Next: **[Module 15 — Exception Handling](../15-exception-handling/README.md)**.
