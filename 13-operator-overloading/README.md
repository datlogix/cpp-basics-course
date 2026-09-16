# Module 13 — Operator Overloading

You've used overloaded operators constantly without necessarily
noticing: `std::cout << x` works whether `x` is an `int`, a `double`, or
a `std::string`, because `<<` is overloaded for each of them
(conceptually similar to the function overloading from Module 7).
This module teaches you to do the same for your **own** classes — so a
class you design can be added, compared, or printed with the same
natural syntax as a built-in type.

## Why bother?

Without operator overloading, combining two custom objects needs an
awkward named method:

```cpp
Complex c3 = c1.add(c2);        // works, but doesn't read naturally
```

With operator overloading:

```cpp
Complex c3 = c1 + c2;           // reads exactly like arithmetic
```

This isn't just cosmetic. Code that manipulates your custom types
becomes readable using the same mental model as ordinary arithmetic —
genuinely valuable for types that represent mathematical objects (as in
the Electrical Engineering track below, where impedance in AC circuits
is literally complex-number arithmetic).

## Overloading `+` (and other binary operators)

```cpp
class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    double getReal() const { return real; }
    double getImag() const { return imag; }
};

int main() {
    Complex a(3, 4);
    Complex b(1, 2);
    Complex c = a + b;   // calls a.operator+(b) behind the scenes
    std::cout << c.getReal() << " + " << c.getImag() << "i" << std::endl;
    return 0;
}
```

- `operator+` is a method whose name is literally `operator` followed by
  the symbol. `a + b` is translated by the compiler into `a.operator+(b)`.
- `const Complex& other` — take the right-hand operand by `const`
  reference: `const` because we only need to read it, not modify it;
  reference to avoid an unnecessary copy (Module 7 principles, still
  applying here).
- The trailing `const` on the method itself promises this operator
  doesn't modify `a`. Get in the habit of marking any method `const`
  when it doesn't change the object — it lets the compiler catch you if
  you accidentally try to.

## Overloading `==` (and other comparisons)

```cpp
bool operator==(const Complex& other) const {
    return real == other.real && imag == other.imag;
}
```

Once defined, `if (a == b)` works exactly like comparing built-in types.
Without this, comparing two objects with `==` either fails to compile or
(for some types) compares memory addresses instead of actual content —
almost never what you want for a value-like class.

## Overloading `<<` for printing — a special case

You'll naturally want `std::cout << myObject` to work. This one is
different: `<<` needs to be a method of `std::ostream` (the stream
class), not of your class — and you can't add methods to a class you
don't own. The fix is a **free function** (not a class member) marked as
a `friend` so it can still reach your class's private data:

```cpp
class Complex {
private:
    double real, imag;
public:
    Complex(double r, double i) : real(r), imag(i) {}
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real << " + " << c.imag << "i";
    return os;
}

int main() {
    Complex c(3, 4);
    std::cout << c << std::endl;   // "3 + 4i"
    return 0;
}
```

Treat this one as a template to copy and adapt rather than something to
derive from first principles — the pattern (`friend`, take/return
`std::ostream&`) is always the same shape.

## Which operators are worth overloading?

A practical rule, not a hard law: overload an operator only when its
built-in *meaning* genuinely fits your type. `+` for combining two
`Complex` numbers or two `Dosage` amounts makes sense — the reader's
intuition about `+` transfers correctly. Overloading `+` to mean
something unrelated to addition (say, "merge two unrelated employee
records") makes code *harder* to read, not easier, because it violates
the reader's correct expectations. When in doubt, a clearly named method
is often the better choice.

## Common beginner mistakes

- Forgetting `const` on the parameter or the method itself, then being
  surprised the operator won't work with temporary/`const` objects.
- Trying to overload `<<` as a regular member method — it must be a free
  function (typically a `friend`) because the left-hand side is a
  `std::ostream`, not your class.
- Overloading an operator with a meaning unrelated to its conventional
  one, making code that uses it confusing rather than natural.
- Forgetting that `operator+` should typically *return a new object*
  rather than modifying either operand — `a + b` shouldn't change `a`
  or `b`.

## Try it yourself

1. Work through [`examples/`](examples/).
2. Complete [`exercises/exercise1.cpp`](exercises/exercise1.cpp).
3. Build the [module project](project/README.md) — pick the Generic,
   EE, or Biomedical track.
4. Commit:

   ```bash
   git add 13-operator-overloading
   git commit -m "Complete Module 13: operator overloading"
   git push
   ```

Next: **[Module 14 — File I/O](../14-file-io/README.md)**.
