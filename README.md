# lscc : the langproc coursework C compiler

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

To run the comprehensive testing suite:

```
chmod u+x test/all.sh
test/all.sh
```

This will test makefile, build process, lexer, parser, and code generation. It will output a summary of the test results in an HTML page at test/out/summary.html

### Checking makefile dependencies

Makefile correctness can be checked by installing [make2graph](https://github.com/lindenb/makefile2graph) and running `test/makefile.sh` from the base directory.

### Testing the tokeniser

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

#### Running tests

To execute all unit tests, run `test/unit.sh`.

To execute all unit tests through gcc instead of lscc, run `test/unit.sh gcc`.

To run a single unit test, run `test/c_files/framework/unit.sh <mode> <testname>` where mode is `lscc` or `gcc`, and testname is the name of the unit test without the .c extension.
