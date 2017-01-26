#ifndef AST_CASE_STATEMENT_H
#define AST_CASE_STATEMENT_H

#include <string>
#include <vector>

#include "../Node.hpp"
#include "../Statement.hpp"
#include "../Expression.hpp"

/* ************************* */

class CaseStatement : public Statement {
public:
	CaseStatement();
	CaseStatement(Expression* e, Statement* s);

	Expression* case_match; // if null, treat as "default" case
	Statement* statement;

	virtual void Debug(std::ostream& dst, int indent) const;
};

#endif
