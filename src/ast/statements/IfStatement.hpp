#ifndef AST_IF_STATEMENT_H
#define AST_IF_STATEMENT_H

#include <string>
#include <vector>

#include "../Node.hpp"
#include "../Statement.hpp"
#include "../Expression.hpp"

/* ************************* */

class IfStatement : public Statement {
public:
	IfStatement();
	IfStatement(Expression* c, Statement* t, Statement* f);

	Expression* condition;
	Statement* true_body;
	Statement* false_body;

	virtual void Debug(std::ostream& dst, int indent) const;
	virtual void PrintXML(std::ostream& dst, int indent) const;
};

#endif
