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
	Expression();

public:
	int sourceLine;
	std::string sourceFile;

	virtual void Debug(std::ostream& dst, int indent) const;

	virtual Type GetType(VariableMap const& bindings) const = 0;

	// TODO : make these two functions pure virtual once all are implemented
	virtual std::string MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const;
	virtual std::string MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const;

	virtual int32_t evaluate_int(VariableMap const& bindings) const;
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
