# Module 16 — The STL: Containers & Iterators

`std::vector` (Module 5) is one member of a much larger toolkit: the
**Standard Template Library (STL)**. This module introduces two more
containers you'll reach for constantly — `std::map` and `std::set` —
plus **iterators**, the general mechanism the STL uses to walk through
any container uniformly.

## `std::map` — key/value lookup

A `vector` is indexed by *position* (`0`, `1`, `2`, ...). A `map` is
indexed by a **key** of your choice — a name, an ID, anything
comparable:

```cpp
#include <map>

std::map<std::string, double> componentValues;

componentValues["R1"] = 220.0;
componentValues["C1"] = 0.000001;
componentValues["L1"] = 0.05;

std::cout << componentValues["R1"] << std::endl;   // 220
```

- `std::map<KeyType, ValueType>` — another template, like `vector<T>`,
  now with two type parameters.
- `map["key"] = value` — inserts a new key, or **overwrites** the value
  if the key already exists.
- Looking up a key that doesn't exist with `[ ]` silently **creates** it
  with a default value (`0` for numbers, `""` for strings) — this is a
  common, surprising gotcha. To check existence without accidentally
  creating an entry, use `.count(key)` or `.find(key)`:

```cpp
if (componentValues.count("R2") == 0) {
    std::cout << "R2 not found." << std::endl;
}
```

### Looping over a map

```cpp
for (const auto& pair : componentValues) {
    std::cout << pair.first << " = " << pair.second << std::endl;
}
```

- `pair.first` is the key, `pair.second` is the value — every element of
  a `map` is a `std::pair<const KeyType, ValueType>`.
- `auto` tells the compiler "figure out the type yourself" — genuinely
  useful here, since writing out the full pair type by hand is verbose.
  Use `auto` when the type is obvious from context or painfully long to
  spell out; still prefer explicit types (as the rest of this course
  does) when the type itself is part of what makes the code readable.
- A `map` is automatically kept sorted by key — looping over it always
  visits keys in ascending order, with no extra work from you.

## `std::set` — a collection of unique values

```cpp
#include <set>

std::set<std::string> uniquePatientIds;
uniquePatientIds.insert("P001");
uniquePatientIds.insert("P002");
uniquePatientIds.insert("P001");   // duplicate - silently ignored

std::cout << uniquePatientIds.size() << std::endl;   // 2, not 3
```

A `set` automatically rejects duplicates and, like `map`, stays sorted.
Reach for it whenever "no duplicates allowed" is a rule your data must
follow — letting the container enforce it is more reliable than checking
manually every time you insert.

## Iterators — the general "walk through this" mechanism

Every STL container supports **iterators** — an object that points to
one element and knows how to move to the next:

```cpp
std::vector<int> scores = {90, 85, 77};

for (std::vector<int>::iterator it = scores.begin(); it != scores.end(); ++it) {
    std::cout << *it << std::endl;
}
```

- `.begin()` — an iterator pointing to the first element.
- `.end()` — an iterator pointing *just past* the last element (never
  dereference this one directly — it's a boundary marker, not a real
  element).
- `*it` — dereference the iterator to get the value, exactly like
  dereferencing a pointer (Module 10) — this is not a coincidence; a
  raw pointer *is* a valid iterator for a plain array.
- `++it` — advance to the next element.

You already know a *shortcut* for this exact loop: the range-based
`for (int score : scores)` from Module 5. Under the hood, the compiler
translates a range-based `for` into precisely this iterator loop — now
you know what it was hiding. Use the range-based form by default; reach
for an explicit iterator when you need the position itself (to erase an
element, or to advance by more than one step).

### Erasing while iterating — a real gotcha

```cpp
std::vector<int> numbers = {1, 2, 3, 4, 5};

for (auto it = numbers.begin(); it != numbers.end(); ) {
    if (*it % 2 == 0) {
        it = numbers.erase(it);   // erase returns the NEXT valid iterator
    } else {
        ++it;                      // only advance if we didn't erase
    }
}
```

Erasing invalidates the iterator you just used — this is exactly why
`.erase(it)` **returns** the next valid iterator, and why this loop
does *not* have `++it` in its header (that would skip an element after
every erase, or use an already-invalidated iterator). This pattern is
worth recognizing even if you don't need it often.

## Choosing a container: a practical guide

| Need | Use |
|------|-----|
| An ordered list, indexed by position, duplicates allowed | `std::vector` |
| Look values up by a name/ID rather than position | `std::map` |
| A collection with no duplicates allowed, order doesn't matter to you | `std::set` |

## Common beginner mistakes

- Using `map["key"]` to check existence — it silently creates the key.
  Use `.count()` or `.find()` instead.
- Forgetting `#include <map>` or `#include <set>`.
- Dereferencing `.end()` directly — it's a boundary, not an element.
- Writing `++it` in an erase loop unconditionally, skipping elements or
  using an invalidated iterator.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — pick the Generic,
   EE, or Biomedical track.
4. Commit:

   ```bash
   git add 16-stl-containers
   git commit -m "Complete Module 16: STL containers and iterators"
   git push
   ```

Next: **[Module 17 — STL Algorithms & Lambdas](../17-stl-algorithms-lambdas/README.md)**.
