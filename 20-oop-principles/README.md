# Module 20 — OOP Principles & Object Modelling

Welcome to **Part 3**. In Parts 1 and 2 you learned the *mechanics* of
object-oriented programming: how to write a `class` (Module 8), how to
derive one class from another (Module 11), how to make `virtual`
methods dispatch correctly (Module 12), and how to make your classes
support natural operators (Module 13).

Knowing the mechanics is not the same as knowing how to **design** with
objects. A student who knows every keyword can still produce a program
that's hard to read, hard to change, and full of bugs. Part 3 is about
the second skill: **thinking in objects** — deciding *which* classes a
program should have, *what* each one is responsible for, *how* they
relate to each other, and *who* owns what.

This first module doesn't add any new syntax at all. It steps back and
gives you the vocabulary and the thinking tools that every later
module in Part 3 builds on.

## A new compile command for Part 3

From now on, compile every example, exercise, and project like this:

```bash
g++ -std=c++17 -Wall -Wextra file.cpp -o file
./file
```

- `-std=c++17` tells the compiler exactly which version of the C++
  language to use. Different compilers default to different versions;
  naming one explicitly means your code behaves the same on every
  machine. (A couple of later modules use a few C++20 features — they
  will tell you to switch to `-std=c++20` when they do.)
- `-Wall -Wextra` turn on **warnings**. A warning is the compiler
  saying "this compiles, but it looks like a mistake." Professional
  programmers treat warnings as bugs waiting to happen. Get into the
  habit now: **a clean build has zero warnings**, not just zero errors.

## Procedural vs. object-oriented: the same problem, two ways

Imagine a small school library. It needs to track books and whether
each book is currently borrowed.

**The procedural way** (how you might have written it in Part 1,
Modules 5–6) keeps the data in separate, parallel vectors and writes
free functions that operate on them:

```cpp
std::vector<std::string> titles;
std::vector<bool> isBorrowed;

void borrowBook(std::vector<bool>& borrowed, int index) {
    borrowed[index] = true;
}
```

This works for a small program, but notice the problems:

- Nothing stops *any* part of the program from writing
  `isBorrowed[3] = false;` directly, skipping whatever rules
  `borrowBook` was supposed to enforce.
- `titles` and `isBorrowed` must always stay the same length and in the
  same order. If one function adds a title but forgets to add a
  matching `false`, every book after it is now wrong — and the compiler
  can't help you.
- Every function needs the vectors passed in. The *data* and the
  *operations on that data* live in different places.

**The object-oriented way** puts the data and the rules for that data
in the same place:

```cpp
class Book {
private:
    std::string title;
    bool borrowed = false;

public:
    Book(std::string t) : title(t) {}

    bool borrow() {
        if (borrowed) {
            return false;   // already out - refuse
        }
        borrowed = true;
        return true;
    }

    void giveBack() { borrowed = false; }
    bool isBorrowed() const { return borrowed; }
    std::string getTitle() const { return title; }
};
```

Now a `Book` *cannot* get into a nonsense state: there's no separate
`isBorrowed` vector to fall out of step, and the only way to borrow a
book is through `borrow()`, which enforces the rule "you can't borrow a
book that's already out."

Run [`examples/01_procedural_version.cpp`](examples/01_procedural_version.cpp)
and [`examples/02_object_version.cpp`](examples/02_object_version.cpp)
side by side. They do the same job. Read both and ask yourself: *which
one would I rather change in six months, when the library also wants
due dates and borrower names?*

> **Neither style is "wrong".** Small scripts are often clearer as a
> few functions. OOP earns its place as programs grow — when there are
> many kinds of things, many rules about them, and many people (or
> many future versions of you) changing the code.

## The four pillars of OOP

Almost every book on object-oriented programming describes four core
ideas. You have already *used* all four; now you'll be able to name
them, which matters, because naming an idea is what lets you reason
about it and discuss it with other programmers.

### 1. Encapsulation — "keep the data and its rules together, and guard them"

Bundle data with the methods that operate on it, and make the data
`private` so the outside world must go through those methods.
`Book::borrow()` above is encapsulation: the `borrowed` flag can only
change in ways the class allows. *(You met this in Module 8.)*

### 2. Abstraction — "show what it does, hide how it does it"

A user of a class should only need to know **what** it does, not
**how**. When you call `std::vector::push_back`, you don't know (or
care) how the vector grows its memory — you know it adds an element.
Your own classes should offer the same courtesy: a `Library` class
might offer `findBook("Things Fall Apart")` without the caller knowing
whether it searches a vector, a `map`, or a file.

Encapsulation and abstraction are related but different:
**encapsulation** is about *protecting* the data; **abstraction** is
about *simplifying* what the user has to think about.

### 3. Inheritance — "this is a more specific kind of that"

A derived class reuses and extends a base class, modelling an "is-a"
relationship: a `TextBook` *is a* `Book`. *(Module 11.)*

### 4. Polymorphism — "one interface, many behaviours"

Code written against a base class works correctly with every derived
class, because `virtual` calls the *actual* object's version at
runtime. One loop over `std::vector<Book*>` can handle `TextBook`,
`Novel`, and `Magazine` without checking which is which. *(Module 12.)*

[`examples/03_four_pillars.cpp`](examples/03_four_pillars.cpp) shows
all four pillars in one short program, each labelled with a comment.

## Finding the classes: from a problem statement to a design

The hardest question in OOP is often the very first one: **"what
classes should I write?"** A simple, reliable starting technique is
**noun/verb analysis**:

1. Write the problem down in plain sentences.
2. Underline the **nouns** — these are *candidate classes* or
   *attributes* (data).
3. Underline the **verbs** — these are *candidate methods*
   (behaviour).
4. Throw away the candidates that are duplicates, too vague, or really
   just a single value.

**Worked example.** Here is a problem statement for a school fees
system:

> A **school** enrols **students**. Each **student** has a **name**, a
> **student ID**, and a **fee account**. The **fee account** records
> **payments** and knows the **balance** still owed. A **bursar**
> **records** a **payment** of an **amount** on a **date**, and can
> **print** a **statement** for any student.

| Noun | Decision | Why |
|---|---|---|
| School | Class | Holds and manages many students |
| Student | Class | Has its own data and identity |
| name, student ID | Attributes of `Student` | Single values, not things with behaviour |
| Fee account | Class | Has data (payments) *and* rules (balance) |
| Payment | Class (small) | Groups amount + date together |
| amount, date | Attributes of `Payment` | Single values |
| balance | Calculated by `FeeAccount` | Derived from payments — don't store it twice |
| Bursar | **Not** a class (yet) | It's the *user* of the program, not something the program models |
| Statement | **Not** a class | It's the *output* of a method |

| Verb | Becomes |
|---|---|
| enrols | `School::enrol(Student)` |
| records a payment | `FeeAccount::recordPayment(Payment)` |
| knows the balance | `FeeAccount::balance()` |
| print a statement | `Student::printStatement()` (or `FeeAccount`'s) |

Notice the judgement calls. "Balance" *sounds* like data, but storing
it separately from the list of payments would create exactly the
"two things that must stay in step" problem we saw with parallel
vectors. Calculating it from the payments makes the bug impossible.
[`examples/04_from_nouns_to_classes.cpp`](examples/04_from_nouns_to_classes.cpp)
turns this table into working code.

> Noun/verb analysis is a **starting point, not an algorithm**. Your
> first list will always need trimming and adjusting. That's normal —
> design is iterative.

## Responsibilities: what does each class *know* and *do*?

Once you have candidate classes, give each one a clear job. A popular
low-tech tool is the **CRC card** (Class–Responsibilities–
Collaborators): a small index card (or a few lines in a text file) per
class:

```
+------------------------------------------------------+
| FeeAccount                                           |
+--------------------------------+---------------------+
| Responsibilities               | Collaborators       |
|  - knows total fees charged    |  - Payment          |
|  - records payments            |                     |
|  - calculates balance owed     |                     |
|  - rejects negative payments   |                     |
+--------------------------------+---------------------+
```

Good responsibilities share one theme. If a card starts to say
"records payments, **and** sends SMS reminders, **and** prints the
school timetable", the class is trying to do too much. (Module 33 gives
this idea a formal name: the *Single Responsibility Principle*.)

## Drawing a design: UML class diagrams

**UML** (Unified Modelling Language) is a standard way to *draw*
classes so that any programmer can read your design without reading
your code. You'll use a simple text version throughout Part 3:

```
+-----------------------------+
|          FeeAccount         |   <- class name
+-----------------------------+
| - totalFees : double        |   <- attributes ("-" = private)
| - payments : vector<Payment>|
+-----------------------------+
| + recordPayment(p : Payment)|   <- methods ("+" = public)
| + balance() : double        |
+-----------------------------+
```

The symbols in front of each member show its access level:

| Symbol | Meaning |
|---|---|
| `+` | `public` |
| `-` | `private` |
| `#` | `protected` |

Relationships between classes are drawn as lines. You already know one:

```
     +--------+
     |  Book  |
     +--------+
         ^
         |          (hollow triangle arrow = "inherits from" / "is-a")
     +----------+
     | TextBook |
     +----------+
```

Module 27 introduces the other relationship lines ("has-a", "uses",
"knows-about"). For now, being able to read and draw a box with `+`/`-`
members and an inheritance arrow is enough.

## Common beginner mistakes

- **Making everything a class.** `Name`, `Amount`, and `Date` don't
  need to be classes just because they're nouns. If something is a
  single value with no rules, it's usually an attribute.
- **Making one giant class.** A single `SchoolSystem` class with 40
  methods is procedural code wearing a `class` costume. Split it by
  responsibility.
- **Storing the same fact twice.** Keeping both a list of payments
  *and* a separate `balance` variable means they can disagree. Calculate
  derived values instead of storing them, unless you have a strong
  reason (and then guard them carefully).
- **Public data "just for now."** Every public attribute is a door
  anyone can walk through. Start `private`; open up only what's needed.
- **Ignoring warnings.** Compiling with `-Wall -Wextra` is only useful
  if you read and fix what it tells you.
- **Designing in your head only.** Ten minutes of nouns, verbs, and a
  rough UML sketch on paper saves hours of rewriting code.

## Try it yourself

1. Work through [`examples/`](examples/), compiling each one with the
   new Part 3 command.
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — pick the Generic,
   EE, or Biomedical track. This module's project is mostly *design*,
   with a small amount of code: that's intentional.
4. Commit:

   ```bash
   git add 20-oop-principles
   git commit -m "Complete Module 20: OOP principles and object modelling"
   git push
   ```

Next: **[Module 21 — Class Design in Depth](../21-class-design/README.md)**.
