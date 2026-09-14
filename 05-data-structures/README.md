# Module 5 — Data Structures

Every variable you've declared so far holds exactly **one** value. Real
programs need to hold *many* related values — a class full of student
scores, a shopping cart of items, a to-do list. This module covers the
four ways you'll do that as a beginner: **arrays**, **`std::vector`**,
**`std::string`** (revisited properly), and **`struct`**.

## Arrays — a fixed-size list of the same type

```cpp
int scores[5] = {90, 85, 77, 92, 60};

std::cout << scores[0] << std::endl;  // 90 - the FIRST element
std::cout << scores[4] << std::endl;  // 60 - the LAST element (index = size - 1)
```

**Indexing starts at 0.** This trips up every beginner at least once: a
5-element array has valid indices `0, 1, 2, 3, 4` — there is no
`scores[5]`. Accessing `scores[5]` doesn't necessarily crash — it may
silently read garbage memory (**undefined behavior**), which is far more
dangerous than a crash because your program can appear to "work" while
being wrong.

### Looping over an array

```cpp
const int SIZE = 5;
int scores[SIZE] = {90, 85, 77, 92, 60};

for (int i = 0; i < SIZE; i++) {
    std::cout << "Score " << i << ": " << scores[i] << std::endl;
}
```

Storing the size in a named `const` (rather than typing `5` in two
places) means if you change the array's size later, you only change it
in one place.

### The core limitation of arrays

An array's size is **fixed at compile time** — you can't grow or shrink
it. In practice, this makes plain arrays a poor fit for anything whose
size changes while the program runs (adding items to a cart, students
enrolling). That's exactly the gap `std::vector` fills.

## `std::vector` — a list that can grow and shrink

```cpp
#include <vector>

std::vector<int> scores = {90, 85, 77};
scores.push_back(92);       // add an element to the end
scores.pop_back();          // remove the last element

std::cout << scores.size() << std::endl;   // how many elements right now
std::cout << scores[0] << std::endl;        // indexing works just like arrays
```

- `<type>` in `std::vector<int>` — this is a **template**: `vector` is a
  general-purpose "list of X" container, and `<int>` says what X is here.
  You'll see this same `<>` pattern again.
- `.push_back(value)` — add to the end.
- `.size()` — current element count (this replaces manually tracking a
  separate size constant).
- Indexing (`scores[i]`) works exactly like arrays, including the same
  "index out of bounds is dangerous" warning.

**Default to `std::vector` over plain arrays** for anything in this
course going forward, unless you specifically know the size will never
change. It's more flexible and just as easy to use.

### Looping over a vector

```cpp
for (int i = 0; i < scores.size(); i++) {
    std::cout << scores[i] << std::endl;
}

// Or, when you don't need the index at all - a "range-based for loop":
for (int score : scores) {
    std::cout << score << std::endl;
}
```

The second form reads "for each `score` in `scores`" — cleaner whenever
you don't need to know the position, only the values.

## `std::string` revisited — a string is a sequence too

You met `std::string` in Module 2 as "a type for text." It's also a
sequence you can index and loop over, just like a vector of characters:

```cpp
std::string name = "Ama";

std::cout << name[0] << std::endl;         // 'A'
std::cout << name.length() << std::endl;   // 3
name += "!";                                // append, just like push_back conceptually
std::cout << name << std::endl;             // "Ama!"

for (char c : name) {
    std::cout << c << std::endl;            // prints each character on its own line
}
```

## `struct` — grouping *different* types together

Arrays and vectors group many values of the **same** type. A `struct`
groups related values of **different** types under one name — the first
step toward the "objects" you'll formalize in Module 8.

```cpp
struct Student {
    std::string name;
    int age;
    double gpa;
};

int main() {
    Student s1;
    s1.name = "Kofi";
    s1.age = 20;
    s1.gpa = 3.7;

    std::cout << s1.name << " is " << s1.age << " with GPA " << s1.gpa << std::endl;

    return 0;
}
```

- `struct Student { ... };` defines a new **type** called `Student` — a
  blueprint, not a variable yet. Notice the `;` after the closing `}` —
  easy to forget, and the compiler error if you do is often confusing.
- `Student s1;` creates an actual `Student` **variable** ("instance") from
  that blueprint.
- `.` (the "dot operator") accesses a member: `s1.name`, `s1.age`.

### Combining what you've learned: a vector of structs

This is one of the most useful patterns in real programs — and exactly
what this module's project uses:

```cpp
std::vector<Student> classroom;

Student s1;
s1.name = "Kofi";
s1.age = 20;
s1.gpa = 3.7;
classroom.push_back(s1);

for (Student s : classroom) {
    std::cout << s.name << ": " << s.gpa << std::endl;
}
```

A "list of records", each with several named fields, is the shape of an
enormous amount of real-world data — this pattern will feel familiar for
the rest of your programming life.

## Common beginner mistakes

- Off-by-one on array/vector size: valid indices are `0` to `size - 1`,
  never `size` itself.
- Forgetting the `;` after a `struct` definition's closing `}`.
- Trying to `.push_back()` on a plain array (arrays don't have this — only
  `std::vector` does).
- Forgetting `#include <vector>` when using `std::vector`.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — a Student Grade
   Tracker (this becomes the seed of the course capstone).
4. Commit:

   ```bash
   git add 05-data-structures
   git commit -m "Complete Module 5: data structures"
   git push
   ```

Next: **[Module 6 — Functions I](../06-functions-i/README.md)**.
