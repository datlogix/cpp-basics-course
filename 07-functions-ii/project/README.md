# Module 7 Project — Recursive Toolkit + Rock-Paper-Scissors

## Part A: Recursive Toolkit

Write these three recursive functions and demonstrate each in `main`:

1. `int power(int base, int exponent)` — computes `base^exponent` without
   using any loop or `pow()`. Base case: `exponent == 0` returns `1`.
2. `int sumDigits(int n)` — sums the digits of a positive integer, e.g.
   `sumDigits(1234)` returns `10`. Hint: the last digit of `n` is
   `n % 10`, and the rest is `n / 10` (integer division drops it).
3. `bool isPalindrome(std::string s, int left, int right)` — returns
   whether `s` reads the same forwards and backwards, by comparing
   `s[left]` and `s[right]` and recursing inward. Base case: when
   `left >= right`.

## Part B: Rock-Paper-Scissors, refactored into functions

You may have written a version of this game before using only `if`
chains. Rebuild it properly using functions:

1. `int getComputerChoice()` — returns 0 (rock), 1 (paper), or 2
   (scissors), randomly (`rand() % 3` — see the random-number snippet in
   Module 4's project README).
2. `std::string choiceToString(int choice)` — converts 0/1/2 to
   `"rock"`/`"paper"`/`"scissors"`.
3. `int determineWinner(int playerChoice, int computerChoice)` — returns
   `1` if the player wins, `-1` if the computer wins, `0` for a tie.
4. In `main`: read the player's choice, get the computer's choice, print
   both as words (using `choiceToString`), call `determineWinner`, and
   print the result. Wrap it in a loop so the player can play multiple
   rounds, and track the score using **reference parameters** passed into
   a `void updateScore(int result, int &playerScore, int &computerScore)`
   function.

## Starter files

- [`recursive_toolkit.cpp`](recursive_toolkit.cpp) — Part A.
- [`rps.cpp`](rps.cpp) — Part B.

## When you're done

```bash
g++ recursive_toolkit.cpp -o recursive_toolkit && ./recursive_toolkit
g++ rps.cpp -o rps && ./rps
```

```bash
git add 07-functions-ii
git commit -m "Complete Module 7 project: recursion + rock-paper-scissors"
git push
```
