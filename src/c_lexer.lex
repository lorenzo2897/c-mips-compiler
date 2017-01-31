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

std::string strip_outer_quotes(const char* text);
std::string consume_until_whitespace(char);
void preprocessor_line(const char*);
char parse_char_literal(const char* text);
char* parse_string_literal(const char* text);
std::string escape_text(std::string text);

void yyerror (char const *s);

int currLine = 1;
std::string currentSourceFile = "";
int currentSourceLine = 1;
int currentSourceCol = 1;

#define COUNTCOL currentSourceCol += yyleng

struct TokenEntry {
	std::string TokenText;
	std::string TokenClass;
	std::string TokenType;
	int LineNum;
	std::string SourceFile;
	int SourceLine;
	int SourceCol;

	TokenEntry(std::string text, std::string tkclass, std::string type) :
		TokenText(text),
		TokenClass(tkclass),
		TokenType(type),
		LineNum(currLine),
		SourceFile(currentSourceFile),
		SourceLine(currentSourceLine),
		SourceCol(currentSourceCol)
	{
	}

	void out() {
		fprintf(yyout, "%-20s %-14s %-16s %3d  %-14s %3d\n", TokenText.c_str(), TokenClass.c_str(), TokenType.c_str(), LineNum, SourceFile.c_str(), SourceLine);
	}

	void json() {
		fprintf(yyout, "  {\"Text\" : %s, \"Class\" : %s, \"StreamLine\" : %d, \"SourceFile\" : %s, \"SourceLine\" : %d, \"SourceCol\" : %d},\n",
			escape_text(TokenText).c_str(),
			escape_text(TokenClass).c_str(),
			LineNum,
			escape_text(SourceFile).c_str(),
			SourceLine,
			SourceCol
		);
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

[ ]+			{ COUNTCOL; } /* ignore whitespace */
[\t]+			{ currentSourceCol += 8; }
[\r]+			{ }
[\n]			{ currLine++; currentSourceLine++; yylineno++; currentSourceCol = 1; } /* keep track of line numbers */

"# "[0-9]+" "\".*\".*\n { preprocessor_line(yytext); } /* preprocessor line indicators */

"void"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "TVoid")); COUNTCOL; return TVOID; }
"long"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "TLong")); COUNTCOL; return TLONG; }
"short"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "TShort")); COUNTCOL; return TSHORT; }
"char"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "TChar")); COUNTCOL; return TCHAR; }
"int"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "TInt")); COUNTCOL; return TINT; }
"float"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "TFloat")); COUNTCOL; return TFLOAT; }
"double"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "TDouble")); COUNTCOL; return TDOUBLE; }

"auto"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Auto")); COUNTCOL; return AUTO; }
"const"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Const")); COUNTCOL; return CONST; }
"extern"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Extern")); COUNTCOL; return EXTERN; }
"register"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Register")); COUNTCOL; return REGISTER; }
"static"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Static")); COUNTCOL; return STATIC; }
"volatile"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Volatile")); COUNTCOL; return VOLATILE; }
"unsigned"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Unsigned")); COUNTCOL; return UNSIGNED; }
"signed"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Signed")); COUNTCOL; return SIGNED; }

"struct"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Struct")); COUNTCOL; return STRUCT; }
"typedef"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Typedef")); COUNTCOL; return TYPEDEF; }
"union"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Union")); COUNTCOL; return UNION; }
"enum"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Enum")); COUNTCOL; return ENUM; }

"if"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "If")); COUNTCOL; return IF; }
"else"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Else")); COUNTCOL; return ELSE; }
"while"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "While")); COUNTCOL; return WHILE; }
"do"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Do")); COUNTCOL; return DO; }
"for"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "For")); COUNTCOL; return FOR; }

"goto"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Goto")); COUNTCOL; return GOTO; }
"break"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Break")); COUNTCOL; return BREAK; }
"continue"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Continue")); COUNTCOL; return CONTINUE; }
"return"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Return")); COUNTCOL; return RETURN; }

"switch"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Switch")); COUNTCOL; return SWITCH; }
"case"				{ token_list.push_back(TokenEntry(yytext, "Keyword", "Case")); COUNTCOL; return CASE; }
"default"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "Default")); COUNTCOL; return DEFAULT; }

"sizeof"			{ token_list.push_back(TokenEntry(yytext, "Keyword", "SizeOf")); COUNTCOL; return SIZEOF; }

"."					{ token_list.push_back(TokenEntry(yytext, "Operator", "Dot")); COUNTCOL; return '.'; }
"->"				{ token_list.push_back(TokenEntry(yytext, "Operator", "Arrow")); COUNTCOL; return ARROW; }
","					{ token_list.push_back(TokenEntry(yytext, "Operator", "Comma")); COUNTCOL; return ','; }
";"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Semicolon")); COUNTCOL; return ';'; }
"..."				{ token_list.push_back(TokenEntry(yytext, "Operator", "Ellipsis")); COUNTCOL; return ELLIPSIS; }
"("					{ token_list.push_back(TokenEntry(yytext, "Operator", "OpenParenthesis")); COUNTCOL; return '('; }
")"					{ token_list.push_back(TokenEntry(yytext, "Operator", "CloseParenthesis")); COUNTCOL; return ')'; }
"["					{ token_list.push_back(TokenEntry(yytext, "Operator", "OpenBracket")); COUNTCOL; return '['; }
"]"					{ token_list.push_back(TokenEntry(yytext, "Operator", "CloseBracket")); COUNTCOL; return ']'; }
"{"					{ token_list.push_back(TokenEntry(yytext, "Operator", "OpenBrace")); COUNTCOL; return OPENBRACE; }
"}"					{ token_list.push_back(TokenEntry(yytext, "Operator", "CloseBrace")); COUNTCOL; return CLOSEBRACE; }

"+"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Plus")); COUNTCOL; return '+'; }
"-"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Minus")); COUNTCOL; return '-'; }
"*"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Star")); COUNTCOL; return '*'; }
"/"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Slash")); COUNTCOL; return '/'; }
"%"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Modulo")); COUNTCOL; return '%'; }
"++"				{ token_list.push_back(TokenEntry(yytext, "Operator", "Increment")); COUNTCOL; return INCREMENT; }
"--"				{ token_list.push_back(TokenEntry(yytext, "Operator", "Decrement")); COUNTCOL; return DECREMENT; }

"!"					{ token_list.push_back(TokenEntry(yytext, "Operator", "LogicalNot")); COUNTCOL; return '!'; }
"&&"				{ token_list.push_back(TokenEntry(yytext, "Operator", "LogicalAnd")); COUNTCOL; return LOGICALAND; }
"||"				{ token_list.push_back(TokenEntry(yytext, "Operator", "LogicalOr")); COUNTCOL; return LOGICALOR; }

"&"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Ampersand")); COUNTCOL; return '&'; }
"|"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Pipe")); COUNTCOL; return '|'; }
"^"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Caret")); COUNTCOL; return '^'; }
"~"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Tilde")); COUNTCOL; return '~'; }
"<<"				{ token_list.push_back(TokenEntry(yytext, "Operator", "ShiftLeft")); COUNTCOL; return SHIFTLEFT; }
">>"				{ token_list.push_back(TokenEntry(yytext, "Operator", "ShiftRight")); COUNTCOL; return SHIFTRIGHT; }

"?"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Question")); COUNTCOL; return '?'; }
":"					{ token_list.push_back(TokenEntry(yytext, "Operator", "Colon")); COUNTCOL; return ':'; }

"="					{ token_list.push_back(TokenEntry(yytext, "Operator", "Assign")); COUNTCOL; return '='; }
"+="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignPlus")); COUNTCOL; return ASSIGNPLUS; }
"-="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignMinus")); COUNTCOL; return ASSIGNMINUS; }
"*="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignStar")); COUNTCOL; return ASSIGNSTAR; }
"/="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignSlash")); COUNTCOL; return ASSIGNSLASH; }
"%="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignModulo")); COUNTCOL; return ASSIGNMODULO; }
"&="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignAmpersand")); COUNTCOL; return ASSIGNAMPERSAND; }
"|="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignPipe")); COUNTCOL; return ASSIGNPIPE; }
"^="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignCaret")); COUNTCOL; return ASSIGNCARET; }
"<<="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignLeftShift")); COUNTCOL; return ASSIGNLEFTSHIFT; }
">>="				{ token_list.push_back(TokenEntry(yytext, "Operator", "AssignRightShift")); COUNTCOL; return ASSIGNRIGHTSHIFT; }

"<"					{ token_list.push_back(TokenEntry(yytext, "Operator", "LessThan")); COUNTCOL; return '<'; }
">"					{ token_list.push_back(TokenEntry(yytext, "Operator", "GreaterThan")); COUNTCOL; return '>'; }
"=="				{ token_list.push_back(TokenEntry(yytext, "Operator", "Equals")); COUNTCOL; return EQUALS; }
"!="				{ token_list.push_back(TokenEntry(yytext, "Operator", "NotEquals")); COUNTCOL; return NOTEQUALS; }
"<="				{ token_list.push_back(TokenEntry(yytext, "Operator", "LessOrEqual")); COUNTCOL; return LESSOREQUAL; }
">="				{ token_list.push_back(TokenEntry(yytext, "Operator", "MoreOrEqual")); COUNTCOL; return MOREOREQUAL; }

{CHARLITERAL}		{ token_list.push_back(TokenEntry(yytext, "Constant", "CharLiteral"));
					yylval.c = parse_char_literal(yytext);
					COUNTCOL;
					return CHARLITERAL; }

{STRINGLITERAL}		{ token_list.push_back(TokenEntry(strip_outer_quotes(yytext), "StringLiteral", "StringLiteral"));
					yylval.s = parse_string_literal(yytext);
					COUNTCOL;
					return STRINGLITERAL; }

{OCTINT}			{ token_list.push_back(TokenEntry(yytext, "Constant", "OctInt"));
					for(char* textbuf = yytext; *textbuf; textbuf++) {
						if(*textbuf == '8' || *textbuf == '9') {
							yyerror("syntax error: octal literals only allow digits from 0 to 7");
						}
					}
					yylval.i = strtol(yytext, NULL, 8);
					COUNTCOL;
					return OCTINT; } /* must be before decimal int! */

{DECINT}			{ token_list.push_back(TokenEntry(yytext, "Constant", "DecInt"));
					yylval.i = atoi(yytext);
					COUNTCOL;
					return DECINT; } /* must be after octal int! */

{HEXINT}			{ token_list.push_back(TokenEntry(yytext, "Constant", "HexInt"));
					yylval.i = strtol(yytext, NULL, 16);
					COUNTCOL;
					return HEXINT; }

{FLOATINGDOUBLE}	{ token_list.push_back(TokenEntry(yytext, "Constant", "FloatingPoint"));
					yylval.d = atof(yytext);
					COUNTCOL;
					return FLOATINGDOUBLE; }

{FLOATINGPOINT}		{ token_list.push_back(TokenEntry(yytext, "Constant", "FloatingPoint"));
					yylval.f = atof(yytext);
					COUNTCOL;
					return FLOATINGPOINT; }

{IDENTIFIER}		{ token_list.push_back(TokenEntry(yytext, "Identifier", "Identifier"));
					yylval.s = strdup(yytext);
					COUNTCOL;
					return IDENTIFIER; }

.					{
						std::string val = consume_until_whitespace(*yytext);
						token_list.push_back(TokenEntry(val, "Invalid", "Invalid"));
						COUNTCOL;
					} /* anything else is invalid */

%%

/* ********************* Subroutines ********************* */

std::string strip_outer_quotes(const char* text) {
	std::string s = text;
	return s.substr(1, s.size() - 2);
}

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
	currentSourceCol = 1;
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
}

std::string escape_text(std::string text) {
	std::string res = "\"";
	for(std::string::iterator itr = text.begin(); itr != text.end(); ++itr) {
		char c = *itr;
		switch (c) {
			case '\a':
				res += "\\a";
				break;
			case '\b':
				res += "\\b";
				break;
			case '\f':
				res += "\\f";
				break;
			case '\n':
				res += "\\n";
				break;
			case '\r':
				res += "\\r";
				break;
			case '\t':
				res += "\\t";
				break;
			case '\v':
				res += "\\v";
				break;
			case '\\':
				res += "\\\\";
				break;
			case '\"':
				res += "\\\"";
				break;
			default:
				res += c;
				break;
		}
	}
	res += "\"";

	return res;
}


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

void print_json_tokens() {
	fprintf(yyout, "\n[\n");
	for(std::vector<TokenEntry>::iterator itr = token_list.begin(); itr != token_list.end(); ++itr) {
		(*itr).json();
	}
	fprintf(yyout, "  {}\n]\n");
}
