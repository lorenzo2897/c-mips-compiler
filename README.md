# lscc : Lorenzo's C compiler

This compiler implements the full 1989 standard of the C programming language, to a high degree of correctness. The program takes pre-processed C code and generates MIPS assembly code.

The compiler was originally created as the coursework component for EIE2 Language Processors, a course in compiler design and implementation, where it achieved the highest mark in the year.

### Approach

The compiler was written in C++ and makes use of the Flex and Bison compiler tools for parsing.

The C source code is parsed, using the Flex tokeniser and Bison parser, into an abstract syntax tree (AST). The program then traverses the AST to analyse variable and stack allocation, while generating an intermediate representation in a flattened low level pseudo-code. Then, the pseudo-code is stripped of any variable names and each statement is translated into a corresponding set of MIPS assembly instructions.

## Building the compiler

Any of the commands below will build the compiler. All executables contain the full functionality, but the default mode of operation depends on the binary that was built.

```
make all
make bin/c_lexer
make bin/c_parser
make bin/c_compiler
make compiler
```

## Compiler command-line options

```
Usage: lscc [OPTIONS] [inputfile] [-o outputfile]

inputfile: Path to .c file, preprocessed wih the GNU C Preprocessor
	if omitted, defaults to stdin

outputfile: Location where the output needs to be sent
	if omitted, defaults to stdout

OPTIONS:

  -v, --version    Display compiler versions

  -h, -?, --help   Display the help menu

  -d, --debug      Send verbose debug output to stderr

  --lex            Tokenise the input, format as table

  --json           Tokenise the input, format as JSON

  --ast            Parse the input into AST, format as text

  --parse          Parse the input into AST, format as XML

  -i, --ir         Compile the C code into an interm. rep.

  -S, --compile    Compile the C code into MIPS assembly


If none specified, defaults to --compile
```

## Testing the compiler

The repository includes a comprehensive testing suite, with automated unit and integration tests for all stages of the compiler. To run the testing suite:

```
chmod u+x test/all.sh
test/all.sh
```

This will test makefile, build process, lexer, parser, and code generation. It will output a summary of the test results in an HTML page at test/out/summary.html

#### Checking makefile dependencies

Makefile correctness can be checked by installing [make2graph](https://github.com/lindenb/makefile2graph) and running `test/makefile.sh` from the base directory.

#### Testing the tokeniser

Run `php test/lexer.php` to generate random C tokens and feed them through the lexer to test its functionality.

Make sure you `make bin/c_lexer` beforehand!

### Creating and running compiler unit tests

Automated unit tests can be carried out using a basic testing framework written in C and bash.

To create a unit test, add a C source file in the `test/c_files/unit/` directory. The file should follow the format:

```c
/*d short test description */
/*@ input_a input_b input_c correct_output */

int func(int a, int b, int c) {
	return 0;
}
```

Note that `func()` is the entry point for the unit test. You may provide as many `/*@ */` test tuples as you wish.

## Running automated unit tests

To execute all unit tests, run `test/unit.sh`.

To execute all unit tests through gcc instead of lscc, run `test/unit.sh gcc`.

To run a single unit test, run `test/c_files/framework/unit.sh <mode> <testname>` where mode is `lscc` or `gcc`, and testname is the name of the unit test without the .c extension.
