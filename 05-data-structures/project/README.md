# Module 5 Project — Student Grade Tracker

Build a program that manages a small classroom of students. This project
directly becomes the seed of the **course capstone** in Module 9 — build
it well.

## Requirements

1. Define a `struct Student` with fields: `std::string name`,
   `std::vector<double> scores`.
2. Create a `std::vector<Student>` and add **at least 3 students**, each
   with **at least 3 scores**.
3. For each student, compute and print their **average score**.
4. Across the whole class, print:
   - The name of the student with the **highest average**.
   - The overall **class average** (average of all students' averages).
5. Use loops and `std::vector` throughout — no plain arrays needed here.

## Example output shape

```
Kofi: average 82.3
Ama: average 91.0
Yaw: average 74.7

Top student: Ama (91.0)
Class average: 82.7
```

## Starter file

Open [`starter.cpp`](starter.cpp).

## When you're done

```bash
g++ starter.cpp -o grade_tracker
./grade_tracker
```

```bash
git add 05-data-structures
git commit -m "Complete Module 5 project: student grade tracker"
git push
```
