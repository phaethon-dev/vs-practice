# C++ Practice

A collection of C++17 exercises and small projects I wrote while building up my C++ fundamentals, from basic loops through classes, inheritance, templates, and a menu-driven banking application. Every component has its own test program, and the whole project builds with a single `make` command.

## Highlights

- **Command-line bank** (`bank_app.cpp`): open checking and savings accounts, deposit, withdraw, transfer, view history, and run month-end interest. All user input is validated before use, and the business rules live in separate, tested classes rather than in the menu code.
- **Type-safe money** (`money.h`): a `Money` value type that stores whole cents to avoid floating-point rounding, with overloaded arithmetic, comparison, and `<<` operators.
- **Input parsing** (`parse.h`): strict parsers for integers and money amounts that return `std::optional` and reject malformed input such as `12.345`, `-5`, `1,000`, or embedded spaces.
- **Library-based build** (`Makefile`): shared code is compiled once into a static library, test programs are discovered automatically, and header dependencies are tracked with `-MMD`.

## What's covered

| Topic | Where |
|---|---|
| Loops, conditionals, off-by-one errors | `fizzbuzz.cpp` |
| Strings and the two-pointer technique | `palindrome.cpp` |
| Hash maps (`std::unordered_map`) | `wordcount.cpp` |
| Stacks | `brackets.cpp`, `stack.h` |
| Structs, sorting with custom comparators, lambdas | `students.h/.cpp`, `grades.cpp` |
| File input and validating messy data | `report.cpp`, `students.txt` |
| Header/source split and linking | `students.h/.cpp` and every class below |
| Classes, encapsulation, invariants, `const` correctness | `gradebook.h/.cpp`, `account.h/.cpp` |
| `static` members | `account.h/.cpp` (shared account-number counter) |
| Inheritance, `virtual`/`override`, polymorphism | `savings.h/.cpp` |
| Abstract classes, interfaces, `std::unique_ptr` | `shapes.h/.cpp` |
| Object lifetime, copy control, `= delete` | `lifetime.cpp`, `account.h` |
| Operator overloading | `money.h/.cpp` |
| Refactoring to a stronger type | `account`/`savings` converted from raw cents to `Money` |
| Function and class templates | `algorithms.h`, `stack.h` |
| `std::optional` and input validation | `parse.h/.cpp` |
| Putting it together | `bank.h/.cpp`, `bank_app.cpp` |

## Building and running

Requires a C++17 compiler (g++) and GNU Make. On Windows I use [MSYS2](https://www.msys2.org/) with the UCRT64 toolchain, where Make is called `mingw32-make`.

```bash
mingw32-make          # build all test programs and the bank app
mingw32-make run      # build, then run every test program
mingw32-make clean    # remove build outputs
```

Run the interactive bank:

```bash
mingw32-make bank_app.exe
./bank_app.exe
```

Each `*_test.cpp` file is a standalone test program that uses `assert` and prints `All tests passed!` on success. The early single-file exercises (`fizzbuzz.cpp`, `palindrome.cpp`, `wordcount.cpp`, `brackets.cpp`, `lifetime.cpp`) can be built on their own, for example:

```bash
g++ -std=c++17 -Wall fizzbuzz.cpp -o fizzbuzz.exe
```

## Project structure

```
Shared library (libpractice.a)
  students   gradebook   account   savings   money   shapes   bank   parse
Header-only
  algorithms.h   stack.h
Programs
  *_test.cpp     one test program per component
  grades.cpp, report.cpp
  bank_app.cpp   interactive banking menu
```
