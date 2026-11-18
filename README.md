# Arbitrary Precision Calculator (APC)

## Project Overview
Developed an Arbitrary Precision Calculator (APC) in C to perform arithmetic operations on large integers beyond the limits of standard C data types.

The project uses **Singly Linked Lists** to store and process individual digits, enabling calculations on numbers of arbitrary length.

## Features
- Addition of large integers
- Subtraction of large integers
- Multiplication of large integers
- Division of large integers
- Support for positive and negative numbers
- Decimal quotient calculation
- Input validation
- Handling of leading zeros

## Technologies Used
- C Programming
- Data Structures
- Singly Linked Lists
- Dynamic Memory Allocation
- Pointers

## Data Structure Implementation
Each digit of the input number is stored as a separate node in a Singly Linked List.

This approach allows the calculator to handle numbers larger than the limits of built-in integer data types.

## Supported Operations

| Operator | Operation |
|---|---|
| + | Addition |
| - | Subtraction |
| x, X, * | Multiplication |
| / | Division |

## Compilation
```bash
gcc *.c -o apc
```

## Execution
```bash
./apc <operand1> <operator> <operand2>
```

### Examples
```bash
./apc 123456789123456789 + 987654321987654321
./apc 987654321 - 123456789
./apc 123456789 x 987654321
./apc 100 / 7
```

## Learning Outcomes
- Practical implementation of Singly Linked Lists
- Dynamic memory allocation and pointer manipulation
- Implementation of arithmetic algorithms
- Handling large integer calculations in C

## Author
**Mohamed Fawaz K.H**

ECE Graduate | Embedded Systems Trainee
