
# BigIntFlex-Cpp


This C++ library provides an implementation of an arbitrarily large signed integer arithmetic, known as BigInteger. It supports operations that exceed the limitations of standard C++ integer types. The BigInteger ADT (Abstract Data Type) uses a List of `long` integers as its underlying data structure to represent the magnitude of the number in a given base, which can be adjusted for performance or precision.

## Features

- **Arbitrary-Size Integers**: Capable of handling integers larger than built-in types without overflow.
- **Supported Operations**: Includes addition, subtraction, multiplication, and advanced arithmetic operations.
- **Base Configuration**: Utilizes a positional numbering system base that is a power of 10, adjustable up to 1,000,000,000 (1 billion) for flexible precision and performance.
- **Normalization**: Automatically manages carries and borrows across digits to maintain a normalized state.
- **Sign Management**: Each BigInteger maintains a sign (positive, negative, or zero), allowing for true signed arithmetic.


## Files

- **BigInteger.h**: Header file defining the BigInteger class and its operations.
- **BigInteger.cpp**: Implementation of the BigInteger ADT, containing the logic for arithmetic operations.
- **List.h**: Modified List ADT header to support `long` elements.
- **List.cpp**: Implementation of the List ADT.
- **Arithmetic.cpp**: Client application demonstrating the use of BigInteger for complex arithmetic operations.
- **BigIntegerTest.cpp**: Tests to verify the functionality and reliability of BigInteger operations.
- **ListTest.cpp**: Tests for the underlying List ADT.
- **Makefile**: Build commands for compiling the projects.
- **README.md**: Documentation of the project components and usage.

## Usage

To compile and run the project:

1. **Compile the project**:
   ```bash
   make
   ```

2. **Run the application**:
   ```bash
   ./Arithmetic <input_file> <output_file>
   ```
   Replace `<input_file>` and `<output_file>` with the names of your input and output files respectively.

## Testing

Detailed tests for both the BigInteger and List ADTs are provided in `BigIntegerTest.cpp` and `ListTest.cpp`. These tests ensure each component functions correctly independently and when integrated.

---

_This README is a part of the BigIntFlex-Cpp Project by Rajat Maheshwari._
