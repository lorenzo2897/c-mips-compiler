#ifndef AST_EXPRESSION_H
#define AST_EXPRESSION_H

#include <iostream>
#include <vector>

#include "Node.hpp"

#include "../intrep/Type.hpp"

extern int currentSourceLine;
extern std::string currentSourceFile;

class Expression : public Node {

protected:

	int sourceLine;
	std::string sourceFile;
	Expression();

public:
	virtual void Debug(std::ostream& dst, int indent) const;

	virtual Type GetType(VariableMap const& bindings) const = 0;

	virtual std::string MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const;
	virtual std::string MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const;
};

/* ************************* */

class CompoundExpression : public Expression {
public:
	std::vector<Expression*> expressions;

	CompoundExpression(Expression* e);

	virtual void Debug(std::ostream& dst, int indent) const;
	void add_expression(Expression* e);

	virtual Type GetType(VariableMap const& bindings) const;

	virtual std::string MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const;
	virtual std::string MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const;
};

#endif
