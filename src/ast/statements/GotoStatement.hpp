#ifndef AST_GOTO_STATEMENT_H
#define AST_GOTO_STATEMENT_H

#include <string>
#include <vector>

#include "../Node.hpp"
#include "../Statement.hpp"

/* ************************* */

class GotoStatement : public Statement {
public:
	GotoStatement();
	GotoStatement(std::string label);

	std::string label;

	virtual void Debug(std::ostream& dst, int indent) const;
};

#endif
