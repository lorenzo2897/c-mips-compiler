#ifndef AST_LABELED_STATEMENT_H
#define AST_LABELED_STATEMENT_H

#include <string>
#include <vector>

#include "../Node.hpp"
#include "../Statement.hpp"

/* ************************* */

class LabeledStatement : public Statement {
public:
	LabeledStatement();
	LabeledStatement(std::string label, Statement* s);

	std::string label;
	Statement* statement;

	virtual void Debug(std::ostream& dst, int indent) const;

	virtual void MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const;
};

#endif
