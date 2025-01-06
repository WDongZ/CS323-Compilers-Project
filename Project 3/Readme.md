# Project Build and Run Instructions

## Prerequisites

Ensure you have the following tools installed on your system:
- `bison`
- `flex`
- `g++` (with support for C++17)

## Build Instructions

**Build the project**:

```sh
make
```

This will:
- Generate the Bison parser files (`syntax.tab.c` and `syntax.tab.h`) from `syntax.y`.
- Generate the Flex lexer file (`lex.yy.c`) from `lex.l`.
- Compile the generated files along with other source files (`symbol.cpp`, `type.cpp`, `ir_generate.cpp`, `three_address_code.cpp`) into the executable `splc` located in the `bin` directory.

## Run Instructions

1. **Run the executable**:
    ```sh
    ./bin/splc <input_file>
    ```

    Replace `<input_file>` with the path to the input file you want to process.

## Clean Up

To remove the generated files and the executable, run:
```sh
make clean