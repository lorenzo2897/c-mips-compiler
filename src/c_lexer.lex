%option noyywrap
%{

#include <cstdio>
#include <cstdlib>

#include <string>
#include <iostream>
#include <vector>

#include "ast/Node.hpp"
#include "ast/Expression.hpp"

#include "c_parser.tab.hpp"


std::string consume_until_whitespace(char);
void preprocessor_line(const char*);
char parse_char_literal(const char* text);
char* parse_string_literal(const char* text);

void yyerror (char const *s);

int currLine = 1;
std::string currentSourceFile = "";
int currentSourceLine = 1;


struct TokenEntry {
	std::string TokenText;
	std::string TokenClass;
	std::string TokenType;
	int LineNum;
	std::string SourceFile;
	int SourceLine;

	TokenEntry(std::string text, std::string tkclass, std::string type) :
		TokenText(text),
		TokenClass(tkclass),
		TokenType(type),
		LineNum(currLine),
		SourceFile(currentSourceFile),
		SourceLine(currentSourceLine)
	{
	}

	void out() {
		fprintf(yyout, "%-20s %-14s %-16s %3d  %-14s %3d\n", TokenText.c_str(), TokenClass.c_str(), TokenType.c_str(), LineNum, SourceFile.c_str(), SourceLine);
	}
};

std::vector<TokenEntry> token_list;

%}

/* ********************* Definitions ********************* */

POWERNOTATION [Ee][+-]?[0-9]+
INTSUFFIX (u|U|l|L)*

OCTINT 0[0-9]+{INTSUFFIX}?
DECINT [0-9]+{INTSUFFIX}?
HEXINT 0(x|X)[0-9a-fA-F]+{INTSUFFIX}?

FP_POWER [0-9]+{POWERNOTATION}
FP_DOTNUM [0-9]*"."[0-9]+({POWERNOTATION})?
FP_NUMDOT [0-9]+"."[0-9]*({POWERNOTATION})?
FLOATINGPOINT ({FP_POWER})|({FP_DOTNUM})|({FP_NUMDOT})(f|F)
FLOATINGDOUBLE ({FP_POWER})|({FP_DOTNUM})|({FP_NUMDOT})(l|L)?

CHARLITERAL L?'(\\.|[^\\'])+'
STRINGLITERAL L?\"(\\.|[^\\"])*\"

IDENTIFIER [A-Za-z_][0-9A-Za-z_]*

/* ************************ Rules ************************ */
%%

[ \t\r]+		{ } /* ignore whitespace */
[\n]			{ currLine++; currentSourceLine++; yylineno++; } /* keep track of line numbers */

"# "[0-9]+" "\".*\".*\n { preprocessor_line(yytext); } /* preprocessor line indicators */

"void"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "TVoid")); return TVOID; }
"long"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "TLong")); return TLONG; }
"short"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "TShort")); return TSHORT; }
"char"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "TChar")); return TCHAR; }
"int"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "TInt")); return TINT; }
"float"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "TFloat")); return TFLOAT; }
"double"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "TDouble")); return TDOUBLE; }

"auto"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Auto")); return AUTO; }
"const"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Const")); return CONST; }
"extern"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Extern")); return EXTERN; }
"register"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Register")); return REGISTER; }
"static"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Static")); return STATIC; }
"volatile"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Volatile")); return VOLATILE; }
"unsigned"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Unsigned")); return UNSIGNED; }
"signed"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Signed")); return SIGNED; }

"struct"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Struct")); return STRUCT; }
"typedef"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Typedef")); return TYPEDEF; }
"union"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Union")); return UNION; }
"enum"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Enum")); return ENUM; }

"if"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "If")); return IF; }
"else"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Else")); return ELSE; }
"while"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "While")); return WHILE; }
"do"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Do")); return DO; }
"for"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "For")); return FOR; }

"goto"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Goto")); return GOTO; }
"break"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Break")); return BREAK; }
"continue"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Continue")); return CONTINUE; }
"return"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Return")); return RETURN; }

"switch"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Switch")); return SWITCH; }
"case"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Case")); return CASE; }
"default"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Default")); return DEFAULT; }

"sizeof"			{ token_list.push_back(TokenEntry(yytext, "Operator", "SizeOf")); return SIZEOF; }

"."					{ token_list.push_back(TokenEntry(yytext, "Operator", "Dot")); return '.'; }
"->"				{ token_list.push_back(TokenEntry(yytext, "Operator", "Arrow")); return ARROW; }
","					{ token_list.push_back(TokenEntry(yytext, "Operator", "Comma")); return ','; }
";"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Semicolon")); return ';'; }
"..."				{ token_list.push_back(TokenEntry(yytext, "Operator", "Ellipsis")); return ELLIPSIS; }
"("					{ token_list.push_back(TokenEntry(yytext, "Operator", "OpenParenthesis")); return '('; }
")"					{ token_list.push_back(TokenEntry(yytext, "Operator", "CloseParenthesis")); return ')'; }
"["					{ token_list.push_back(TokenEntry(yytext, "Operator", "OpenBracket")); return '['; }
"]"					{ token_list.push_back(TokenEntry(yytext, "Operator", "CloseBracket")); return ']'; }
"{"					{ token_list.push_back(TokenEntry(yytext, "Operator", "OpenBrace")); return OPENBRACE; }
"}"					{ token_list.push_back(TokenEntry(yytext, "Operator", "CloseBrace")); return CLOSEBRACE; }

"+"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Plus")); return '+'; }
"-"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Minus")); return '-'; }
"*"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Star")); return '*'; }
"/"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Slash")); return '/'; }
"%"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Modulo")); return '%'; }
"++"				{ token_list.push_back(TokenEntry(yytext, "Operator", "Increment")); return INCREMENT; }
"--"				{ token_list.push_back(TokenEntry(yytext, "Operator", "Decrement")); return DECREMENT; }

"!"					{ token_list.push_back(TokenEntry(yytext, "Operator", "LogicalNot")); return '!'; }
"&&"				{ token_list.push_back(TokenEntry(yytext, "Operator", "LogicalAnd")); return LOGICALAND; }
"||"				{ token_list.push_back(TokenEntry(yytext, "Operator", "LogicalOr")); return LOGICALOR; }

"&"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Ampersand")); return '&'; }
"|"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Pipe")); return '|'; }
"^"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Caret")); return '^'; }
"~"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Tilde")); return '~'; }
"<<"				{ token_list.push_back(TokenEntry(yytext, "Operator", "ShiftLeft")); return SHIFTLEFT; }
">>"				{ token_list.push_back(TokenEntry(yytext, "Operator", "ShiftRight")); return SHIFTRIGHT; }

"?"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Question")); return '?'; }
":"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Colon")); return ':'; }

"="					{ token_list.push_back(TokenEntry(yytext, "Operator", "Assign")); return '='; }
"+="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignPlus")); return ASSIGNPLUS; }
"-="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignMinus")); return ASSIGNMINUS; }
"*="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignStar")); return ASSIGNSTAR; }
"/="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignSlash")); return ASSIGNSLASH; }
"%="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignModulo")); return ASSIGNMODULO; }
"&="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignAmpersand")); return ASSIGNAMPERSAND; }
"|="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignPipe")); return ASSIGNPIPE; }
"^="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignCaret")); return ASSIGNCARET; }
"<<="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignLeftShift")); return ASSIGNLEFTSHIFT; }
">>="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignRightShift")); return ASSIGNRIGHTSHIFT; }

"<"					{ token_list.push_back(TokenEntry(yytext, "Operator", "LessThan")); return '<'; }
">"					{ token_list.push_back(TokenEntry(yytext, "Operator", "GreaterThan")); return '>'; }
"=="				{ token_list.push_back(TokenEntry(yytext, "Operator", "Equals")); return EQUALS; }
"!="				{ token_list.push_back(TokenEntry(yytext, "Operator", "NotEquals")); return NOTEQUALS; }
"<="				{ token_list.push_back(TokenEntry(yytext, "Operator", "LessOrEqual")); return LESSOREQUAL; }
">="				{ token_list.push_back(TokenEntry(yytext, "Operator", "MoreOrEqual")); return MOREOREQUAL; }

{CHARLITERAL}		{ token_list.push_back(TokenEntry(yytext, "Constant", "CharLiteral"));
					yylval.c = parse_char_literal(yytext);
					return CHARLITERAL; }

{STRINGLITERAL}		{ token_list.push_back(TokenEntry(yytext, "StringLiteral", "StringLiteral"));
					yylval.s = parse_string_literal(yytext);
					return STRINGLITERAL; }

{OCTINT}			{ token_list.push_back(TokenEntry(yytext, "Constant", "OctInt"));
					for(char* textbuf = yytext; *textbuf; textbuf++) {
						if(*textbuf == '8' || *textbuf == '9') {
							yyerror("syntax error: octal literals only allow digits from 0 to 7");
						}
					}
					yylval.i = strtol(yytext, NULL, 8);
					return OCTINT; } /* must be before decimal int! */

{DECINT}			{ token_list.push_back(TokenEntry(yytext, "Constant", "DecInt"));
					yylval.i = atoi(yytext);
					return DECINT; } /* must be after octal int! */

{HEXINT}			{ token_list.push_back(TokenEntry(yytext, "Constant", "HexInt"));
					yylval.i = strtol(yytext, NULL, 16);
					return HEXINT; }

{FLOATINGDOUBLE}	{ token_list.push_back(TokenEntry(yytext, "Constant", "FloatingPoint"));
					yylval.d = atof(yytext);
					return FLOATINGDOUBLE; }

{FLOATINGPOINT}		{ token_list.push_back(TokenEntry(yytext, "Constant", "FloatingPoint"));
					yylval.f = atof(yytext);
					return FLOATINGPOINT; }

{IDENTIFIER}		{ token_list.push_back(TokenEntry(yytext, "Identifier", "Identifier"));
					yylval.s = strdup(yytext);
					return IDENTIFIER; }

.					{
						std::string val = consume_until_whitespace(*yytext);
						token_list.push_back(TokenEntry(val, "Invalid", "Invalid"));
					} /* anything else is invalid */

%%

/* ********************* Subroutines ********************* */

std::string consume_until_whitespace(char first) {
	char c = 0;
	std::string s(1, first);

    while ((c = yyinput())) {
		if(c == ' ' || c == '\t' || c == '\r' || c == '\n')
			return s;
		s += c;
    }

	return s;
}

void preprocessor_line(const char* text) {
	// adjust context based on preprocessor line info
	// format: # linenum "filename" flags
	// flags: one or more of the following, separated by spaces
	// 1 : the start of a new file.
	// 2 : returning to a file (after having included another file).
	// 3 : that the following text comes from a system header file, so certain warnings should be suppressed.
	// 4 : that the following text should be treated as being wrapped in an implicit extern "C" block.

	std::string linenum;
	std::string sourcefile;
	bool f_newfile = false;
	bool f_returnfile = false;
	bool f_sysheader = false;
	bool f_externc = false;

	// first character is a hash
	++text;

	// second character is a space
	++text;

	// begin line number until space
	while(char c = *(text++)) {
		if(c == ' ')
			break;
		linenum += c;
	}

	// now there is a double quote
	++text;

	// begin file name until next double quote
	// stupid preprocessor allowing escaped quotes in name...
	bool escape_sequence = false;
	while(char c = *(text++)) {
		if(c == '\\') { // backslash
			if(escape_sequence) {
				escape_sequence = false;
				sourcefile += '\\';
			} else {
				escape_sequence = true;
			}
		} else if(c == '"') { // double quote
			if(escape_sequence) {
				escape_sequence = false;
				sourcefile += '"';
			} else {
				break;
			}
		} else {
			if(escape_sequence) { // other escape sequence
				escape_sequence = false;
				sourcefile += '\\';
			}
			sourcefile += c;
		}
	}

	// now there is a space, followed by flags
	while(char c = *(text++)) {
		if(c == '1') {
			f_newfile = true;
		} else if(c == '2') {
			f_returnfile = true;
		} else if(c == '3') {
			f_sysheader = true;
		} else if(c == '4') {
			f_externc = true;
		}
	}

	currentSourceFile = sourcefile;
	currentSourceLine = atoi(linenum.c_str());
	currLine++;
}

char parse_escape_sequence(const char*& str) {

	// iterate through text as a FSM
	char c;
	bool octal = false;
	bool hex = false;
	unsigned int tmp = 0;

	while((c = *str++)) {
		if(octal || hex) {
			if(octal && (c < '0' || c > '7')) { // end of escape sequence
				--str;
				if(tmp > 255) {
					yyerror("syntax error: octal escape sequence in literal overflowed");
				}
				unsigned char tmpc = (unsigned char) tmp;
				return *((char*) &tmpc);
			} else if(hex && !((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))) { // end of escape sequence
				--str;
				if(tmp > 255) {
					yyerror("syntax error: hex escape sequence in literal overflowed");
				}
				unsigned char tmpc = (unsigned char) tmp;
				return *((char*) &tmpc);
			} else {
				// figure out the value of the digit
				unsigned char v = 0;
				if(c >= '0' && c <= '9') {
					v = c - '0';
				} else if(c >= 'a' && c <= 'f') {
					v = c - 'a';
				} else if(c >= 'A' && c <= 'F') {
					v = c - 'A';
				}
				// add digit to the temporary accumulator
				if(octal) {
					tmp = tmp * 8 + v;
				} else {
					tmp = tmp * 16 + v;
				}
			}
		} else if(c == '\\') {
			return '\\';
		} else if(c == '\'') {
			return '\'';
		} else if(c == 'n') {
			return '\n';
		} else if(c == '"') {
			return '"';
		} else if(c == '?') {
			return '?';
		} else if(c == 'r') {
			return '\r';
		} else if(c == 't') {
			return '\t';
		} else if(c == 'a') {
			return '\a';
		} else if(c == 'b') {
			return '\b';
		} else if(c == 'f') {
			return '\f';
		} else if(c == 'v') {
			return '\v';
		} else if(c == 'x') {
			hex = true;
		} else if(c >= '0' && c <= '7') {
			octal = true;
			tmp = c - '0';
		} else {
			yyerror("syntax error: invalid escape sequence in literal");
		}
	}
	yyerror("syntax error: invalid escape sequence in literal");
	return 0;
}

char parse_char_literal(const char* text) {
	// ignore L prefix
	if(*text == 'L') {
		++text;
	}

	// skip opening single quote
	++text;

	if(*text == '\\') {
		char c = parse_escape_sequence(++text);
		if(*text != '\'') { // there's still stuff in the string
			yyerror("syntax error: invalid escape sequence in character literal");
		}
		return c;
	} else {
		if(*(text+1) != '\'') {
			yyerror("syntax error: character literal too long");
		}
		return *text;
	}
}


char* parse_string_literal(const char* text) {
	// ignore L prefix
	if(*text == 'L') {
		++text;
	}

	// skip opening double quotes
	++text;

	// iterate through the string
	std::string buf;
	char c;
	while((c = *text++)) {
		if(c == '"') {
			break;
		} else if(c == '\\') {
			buf += parse_escape_sequence(text);
		} else {
			buf += c;
		}
	}

	return strdup(buf.c_str());
};


void yyerror (char const *s) {
	if(currentSourceFile != "") {\
		fprintf(stderr, "%s:%d: %s\n", currentSourceFile.c_str(), currentSourceLine, s);
	} else {
		fprintf(stderr, "line %d: %s\n", currLine, s);
	}
	exit(1);
}

/* ******************* Public functions ******************* */

void print_tokens() {
	fprintf(yyout, "Token text           Class          Type            Line  Source file   Line\n"
	"============================================================================\n");
	for(std::vector<TokenEntry>::iterator itr = token_list.begin(); itr != token_list.end(); ++itr) {
		(*itr).out();
	}
	fprintf(yyout, "\nTotal lines = %d\n", currLine);
}
