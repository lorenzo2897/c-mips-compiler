#ifndef AST_RETURN_STATEMENT_H
#define AST_RETURN_STATEMENT_H

#include <string>
#include <vector>

#include "../Node.hpp"
#include "../Statement.hpp"
#include "../Expression.hpp"

/* ************************* */

class ReturnStatement : public Statement {
public:
	ReturnStatement();
	ReturnStatement(Expression* e);

	Expression* expression;

	virtual void Debug(std::ostream& dst, int indent) const;
};

#endif
