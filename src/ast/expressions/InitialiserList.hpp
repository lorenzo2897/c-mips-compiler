#ifndef AST_INITIALISER_LIST_H
#define AST_INITIALISER_LIST_H

#include <iostream>
#include <vector>

#include "../Expression.hpp"

class InitialiserList : public Expression {

public:
	std::vector<Expression*> list;

	void add(Expression* e);

	virtual void Debug(std::ostream& dst, int indent) const;
	virtual Type GetType(VariableMap const& bindings) const;

	virtual std::string MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const;
	virtual std::string MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const;
};

#endif
