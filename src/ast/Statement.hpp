#ifndef AST_STATEMENT_H
#define AST_STATEMENT_H

#include <string>
#include <vector>

#include "Node.hpp"
#include "Expression.hpp"

extern int currentSourceLine;
extern std::string currentSourceFile;

class Statement : public Node {

public:
	Statement();

	int sourceLine;
	std::string sourceFile;

	virtual void Debug(std::ostream& dst, int indent) const;

};

#endif
