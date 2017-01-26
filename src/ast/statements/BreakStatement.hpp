#ifndef AST_BREAK_STATEMENT_H
#define AST_BREAK_STATEMENT_H

#include <string>
#include <vector>

#include "../Node.hpp"
#include "../Statement.hpp"

/* ************************* */

class BreakStatement : public Statement {
public:
	BreakStatement();
	BreakStatement(bool is_continue);

	bool is_continue;

	virtual void Debug(std::ostream& dst, int indent) const;
};

#endif
