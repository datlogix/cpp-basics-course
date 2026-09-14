# Module 0 — Tools: VS Code, a C++ Compiler, Git & GitHub

Before writing a single line of C++, you need three things working
together:

1. A **compiler** — turns the C++ you write into a program the computer
   can run.
2. **VS Code** — where you'll write code, run it, and see errors.
3. **Git & GitHub** — so your work is saved, versioned, and backed up
   online, the way professional developers work.

Do these steps once, carefully, and you won't think about them again.

---

## 1. Install a C++ compiler

You're on **macOS**. The compiler comes from Apple's Command Line Tools.

Open the **Terminal** app and run:

```bash
xcode-select --install
```

If a dialog pops up, click **Install** and wait for it to finish. If you
get a message saying it's already installed, that's fine — you're done.

Verify it worked:

```bash
g++ --version
```

You should see a version number (e.g. `Apple clang version 15.0.0`). If
you see `command not found`, the install didn't complete — re-run the
`xcode-select --install` command.

> **What is `g++`?** It's the command that invokes the C++ compiler.
> Later, "compile `hello.cpp`" always means "run a `g++` command against
> that file."

---

## 2. Install VS Code

1. Go to <https://code.visualstudio.com/> and download **VS Code for
   macOS**.
2. Open the downloaded `.zip`, drag **Visual Studio Code.app** into your
   **Applications** folder.
3. Open VS Code from Applications (or Spotlight: `Cmd+Space`, type
   "Visual Studio Code").

### Install the C/C++ extension

1. Click the **Extensions** icon in the left sidebar (four squares icon),
   or press `Cmd+Shift+X`.
2. Search for **"C/C++"** (published by Microsoft) and click **Install**.
3. Also install **"Code Runner"** (published by Jun Han) — it adds a
   ▶ **Run** button so you can run a `.cpp` file with one click while
   you're learning the terminal commands.

### Open this course folder in VS Code

- In VS Code: **File → Open Folder…** → select `C++ Basics` (the folder
  this README lives inside, one level up).
- Use **View → Terminal** (or `` Ctrl+` ``) to open a terminal *inside*
  VS Code. You'll use this constantly — no need to switch to a separate
  Terminal app.

---

## 3. Compile and run your first program, by hand

Before relying on any "Run" button, do this manually once so you
understand what's actually happening. In the VS Code terminal:

```bash
cd 00-setup
```

Create a file called `hello.cpp` in that folder with this content:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, C++!" << std::endl;
    return 0;
}
```

Compile it:

```bash
g++ hello.cpp -o hello
```

- `g++` — the compiler
- `hello.cpp` — your source file (the C++ you wrote)
- `-o hello` — "output an executable named `hello`"

Run it:

```bash
./hello
```

You should see:

```
Hello, C++!
```

**What just happened:** `g++` read your text file, checked it for
mistakes (syntax errors), translated it into machine instructions, and
produced a file called `hello` — an actual program. `./hello` means "run
the program named `hello` that's in this folder." We unpack every part of
this in [Module 1](../01-basics-of-programming/README.md).

From now on, every module's `examples/` and `exercises/` files are
compiled and run exactly this way, or with the Code Runner ▶ button once
you trust it.

---

## 4. Git & GitHub — saving and backing up your work

**Git** tracks changes to your files over time on your own computer.
**GitHub** is a website that hosts a copy of that history online, so it's
backed up and shareable. You'll use both for every module in this course.

### 4.1 Install Git

Check if it's already there:

```bash
git --version
```

Installing the Xcode Command Line Tools in step 1 also installs Git, so
this should already work. If not, running `xcode-select --install` again
will install it.

### 4.2 Create a GitHub account

1. Go to <https://github.com/> and click **Sign up**.
2. Choose a professional username — you'll link to it from job
   applications and your CV one day, so avoid anything too silly.
3. Verify your email address.

### 4.3 Tell Git who you are

This labels every change you make with your name and email. Run once
(replace with your real name and the email you used for GitHub):

```bash
git config --global user.name "Your Name"
git config --global user.email "your@email.com"
```

### 4.4 Connect VS Code to GitHub

1. In VS Code, click the **Accounts** icon (bottom-left corner, person
   icon).
2. Choose **Sign in with GitHub** and follow the browser prompts to
   authorize VS Code.

You now have a single account working across GitHub.com and VS Code's
Source Control panel.

### 4.5 This course folder is already a Git repository

Good news — the folder you're in (`C++ Basics`) is *already* set up as a
Git repository from earlier work. You can confirm this any time with:

```bash
git status
```

If it prints something like `On branch master`, Git is already tracking
this folder. (If you ever start a brand-new project from scratch, the
command to begin tracking a folder is `git init` — but you won't need it
here.)

### 4.6 The daily workflow: status → add → commit → push

This is the loop you'll repeat constantly, in the terminal or through
VS Code's **Source Control** panel (the icon that looks like a branching
line, `Ctrl+Shift+G`).

**Terminal version:**

```bash
git status              # what changed?
git add <file>          # stage a specific file (or `git add .` for everything shown by status)
git commit -m "Add hello world example from Module 0"
git push
```

- `git status` — shows which files are new or modified.
- `git add` — marks files to be included in the next save point. Prefer
  naming files explicitly over `git add .` so you never accidentally
  commit something you didn't mean to (like a stray download).
- `git commit -m "..."` — creates a save point (a "commit") with a short
  message describing *what changed and why*. Write it in the present
  imperative tense: `"Add"`, not `"Added"` — that's the convention nearly
  every real project follows.
- `git push` — uploads your commits to GitHub.

**VS Code Source Control panel version** (same steps, no terminal):

1. Click the **Source Control** icon. Changed files appear listed.
2. Hover a file and click **+** to stage it (equivalent to `git add`).
3. Type your commit message in the box at the top, then click the
   checkmark ✓ (equivalent to `git commit`).
4. Click **Sync Changes** / the ↑ icon (equivalent to `git push`).

### 4.7 Linking this folder to a repository on GitHub

If this folder isn't pushing anywhere yet, create the remote home for it:

1. On GitHub.com, click **+ → New repository**. Name it (e.g.
   `cpp-basics-course`), leave it **empty** (no README, no .gitignore —
   this folder already has files), and click **Create repository**.
2. GitHub shows you a remote URL like
   `https://github.com/<your-username>/cpp-basics-course.git`. Copy it.
3. Back in the VS Code terminal:

   ```bash
   git remote add origin https://github.com/<your-username>/cpp-basics-course.git
   git branch -M main
   git push -u origin main
   ```

   You only do this **once** per project. Every push after this is just
   `git push`.

### 4.8 A commit habit worth building now

Commit at the end of every example, exercise, and project step —
even the small ones. Real teams work exactly this way: many small,
clearly-described commits, not one giant commit at the end. Future-you
(and any teammate) can look at your commit history and see exactly how
the project grew.

---

## ✅ Checkpoint

Before moving on, confirm all of the following work:

- [ ] `g++ --version` prints a version number
- [ ] You compiled and ran `hello.cpp` and saw `Hello, C++!`
- [ ] You have a GitHub account and are signed in inside VS Code
- [ ] `git status` runs without error inside this folder
- [ ] You made one commit (e.g. adding `hello.cpp`) and pushed it —
      check GitHub.com and confirm the file appears in your repository

Once every box is checked, move on to
**[Module 1 — Basics of Programming](../01-basics-of-programming/README.md)**.
