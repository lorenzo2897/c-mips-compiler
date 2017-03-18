#ifndef AST_SWITCH_STATEMENT_H
#define AST_SWITCH_STATEMENT_H

#include <string>
#include <vector>

#include "../Node.hpp"
#include "../Statement.hpp"
#include "../Expression.hpp"

/* ************************* */

class SwitchStatement : public Statement {
public:
	SwitchStatement();
	SwitchStatement(Expression* e, Statement* s);

	Expression* expression;
	Statement* statement;

	virtual void Debug(std::ostream& dst, int indent) const;

	virtual void MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const;
};

#endif
