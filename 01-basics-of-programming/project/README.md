# Module 1 Project — ASCII Greeting Card

Build a program that prints a small "greeting card" to the terminal using
only what you know so far: `#include`, `main`, `std::cout`, string
literals, and comments.

## Requirements

Your program must print something like this (feel free to design your
own box/art — this is just an example):

```
****************************
*                          *
*   Welcome, Douglas!      *
*   Have a great day.      *
*                          *
****************************
```

1. Use at least **5** separate `std::cout` statements.
2. Include at least **one comment** explaining a design choice you made
   (e.g. why you picked that border character).
3. Personalize it — put your own name and a message you actually like in
   there.

## Stretch goal (optional, but try it)

Print a small ASCII picture (a house, a star, a smiley face — anything
made of characters like `*`, `/`, `\`, `_`, `|`). This is purely
`std::cout` practice — no new concepts needed, just careful counting of
characters and spaces.

## Starter file

Open [`starter.cpp`](starter.cpp) and build your card there.

## When you're done

```bash
g++ starter.cpp -o greeting_card
./greeting_card
```

Then commit it:

```bash
git add 01-basics-of-programming
git commit -m "Complete Module 1 project: ASCII greeting card"
git push
```
