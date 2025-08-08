# Compiler Construction Project

This repository contains a compiler implementation for a custom programming language, developed as an academic project. The compiler includes lexical analysis, syntax analysis, and parse tree generation.

## Project Structure

- **Lexical Analysis**: Implemented in `lexer.c` and `lexer.h`
- **Syntax Analysis**: Implemented in `parser.c` and `parser.h`
- **First and Follow Sets**: Implemented in `firstandfollow.c` and `firstandfollow.h`
- **Utility Functions**: Implemented in `utility.c` and `utility.h`
- **Driver Program**: Implemented in `driver.c`

## Building the Compiler

To build the compiler, run:

```bash
make
```

This will generate the executable `stage1exe`.

## Running the Compiler

To run the compiler, use:

```bash
./stage1exe <source_file> <output_file>
```

Where:
- `<source_file>` is the path to the source code file to be compiled
- `<output_file>` is the path where the parse tree will be written

## Available Commands

Once the compiler is running, you can use the following commands:

1. Print the comment-free code
2. Print the token list
3. Parse the source code to verify syntactic correctness
4. Create and print the parse tree
5. Exit the compiler

## Test Cases

The repository includes several test cases:
- `testcase1.txt` through `testcase5.txt`: Valid test cases
- `errcase1.txt` through `errcase4.txt`: Test cases with errors

## Cleaning Up

To clean up build artifacts, run:

```bash
make clean
```

## Original Authors

- Batch No 11
- Nishant Bansal (2014A7PS052P)
- Subham Kumar (2014A7PS121P)
