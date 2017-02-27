#ifndef AST_WHILE_STATEMENT_H
#define AST_WHILE_STATEMENT_H

#include <string>
#include <vector>

#include "../Node.hpp"
#include "../Statement.hpp"
#include "../Expression.hpp"

/* ************************* */

class WhileStatement : public Statement {
public:
	WhileStatement();
	WhileStatement(Expression* e, Statement* s, bool statement_before_condition);

	Expression* expression;
	Statement* statement;
	bool statement_before_condition;

	virtual void Debug(std::ostream& dst, int indent) const;
	virtual void PrintXML(std::ostream& dst, int indent) const;
};

#endif
