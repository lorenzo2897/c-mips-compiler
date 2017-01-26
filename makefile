OUT = bin
CSOURCES = src/main.cpp src/ast/*.cpp src/ast/expressions/*.cpp src/ast/statements/*.cpp src/c_lexer.yy.cpp src/c_parser.tab.cpp
CHEADERS = src/ast/*.hpp src/ast/expressions/*.hpp src/ast/statements/*.hpp src/c_parser.tab.hpp
GCCOPT = -g

# compiler

compiler : ${CSOURCES} ${CHEADERS}
	g++ ${GCCOPT} ${CSOURCES} -o ${OUT}/lscc

src/c_parser.tab.cpp src/c_parser.tab.hpp : src/c_parser.y
	bison -t -d src/c_parser.y -o src/c_parser.tab.cpp

src/c_lexer.yy.cpp : src/c_lexer.lex src/c_parser.tab.hpp
	flex -o src/c_lexer.yy.cpp src/c_lexer.lex


# intermediate deliverables

${OUT}/c_lexer : compiler
	g++ ${GCCOPT} -Dprogram_mode=lexer ${CSOURCES} -o ${OUT}/c_lexer

${OUT}/c_parser : compiler
	g++ ${GCCOPT} -Dprogram_mode=parser ${CSOURCES} -o ${OUT}/c_parser


# maintenance commands

all : compiler ${OUT}/c_lexer ${OUT}/c_parser

clean :
	rm -f src/c_lexer.yy.cpp
	rm -f src/c_parser.tab.cpp
	rm -f src/c_parser.tab.hpp
	rm -f src/ast/*.gch
	rm -f src/ast/expressions/*.gch
	rm -f src/ast/statements/*.gch
	rm -f ${OUT}/lscc
	rm -f ${OUT}/c_lexer
	rm -f ${OUT}/c_parser
