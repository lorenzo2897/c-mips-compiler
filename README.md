# lscc : the langproc coursework C compiler

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

  -S, --compile    Compile the C code into MIPS assembly


If none specified, defaults to --compile
```

## Testing the compiler

### Checking makefile dependencies

Makefile correctness can be checked by installing [make2graph](https://github.com/lindenb/makefile2graph) and running `test/makefile.sh` from the base directory.

### Testing the tokeniser

Run `php test/lexer.php` to generate random C tokens and feed them through the lexer to test its functionality.

Make sure you `make bin/c_lexer` beforehand!
