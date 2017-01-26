#ifndef AST_EXPRESSION_STATEMENT_H
#define AST_EXPRESSION_STATEMENT_H

#include <string>
#include <vector>

#include "../Node.hpp"
#include "../Statement.hpp"
#include "../Expression.hpp"

/* ************************* */

class ExpressionStatement : public Statement {
public:
	ExpressionStatement();
	ExpressionStatement(Expression* e);

	Expression* expression;
	virtual void Debug(std::ostream& dst, int indent) const;

};

#endif
