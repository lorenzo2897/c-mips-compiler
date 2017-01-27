OUT = bin
CSOURCES = $(wildcard src/ast/*.cpp) $(wildcard src/ast/expressions/*.cpp) $(wildcard src/ast/statements/*.cpp)
OBJS = $(patsubst src/%.cpp,obj/%.o,$(CSOURCES)) obj/c_parser.tab.o obj/c_lexer.yy.o
CHEADERS = src/ast/*.hpp src/ast/expressions/*.hpp src/ast/statements/*.hpp src/c_parser.tab.hpp
GCCOPT = -g

# compiler

compiler : ${OBJS} ${CHEADERS} src/main.cpp
	g++ ${GCCOPT} ${OBJS} src/main.cpp -o ${OUT}/lscc

obj/c_parser.tab.o src/c_parser.tab.hpp : src/c_parser.y
	bison -t -d src/c_parser.y -o src/c_parser.tab.cpp
	g++ -c ${GCCOPT} src/c_parser.tab.cpp -o obj/c_parser.tab.o

obj/c_lexer.yy.o : src/c_lexer.lex src/c_parser.tab.hpp
	flex -o src/c_lexer.yy.cpp src/c_lexer.lex
	g++ -c ${GCCOPT} src/c_lexer.yy.cpp -o obj/c_lexer.yy.o

# object files

obj/ast/%.o : src/ast/%.cpp
	g++ $(GCCOPT) -c -o $@ $<

obj/ast/expressions/%.o : src/ast/expressions/%.cpp
	g++ $(GCCOPT) -c -o $@ $<

obj/ast/statements/%.o : src/ast/statements/%.cpp
	g++ $(GCCOPT) -c -o $@ $<

# intermediate deliverables

${OUT}/c_lexer : compiler
	g++ ${GCCOPT} -Dprogram_mode=lexer ${OBJS} src/main.cpp -o ${OUT}/c_lexer

${OUT}/c_parser : compiler
	g++ ${GCCOPT} -Dprogram_mode=parser ${OBJS} src/main.cpp -o ${OUT}/c_parser


# maintenance commands

all : compiler ${OUT}/c_lexer ${OUT}/c_parser

clean :
	-rm src/c_lexer.yy.cpp
	-rm src/c_parser.tab.cpp
	-rm src/c_parser.tab.hpp
	-rm src/ast/*.gch
	-rm src/ast/expressions/*.gch
	-rm src/ast/statements/*.gch
	-rm -r obj/*
	-rm -r ${OUT}/lscc ${OUT}/lscc.dSYM
	-rm -r ${OUT}/c_lexer ${OUT}/c_lexer.dSYM
	-rm -r ${OUT}/c_parser ${OUT}/c_parser.dSYM
	mkdir -p obj/ast/expressions
	mkdir -p obj/ast/statements
