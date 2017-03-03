#ifndef AST_TERNARY_EXPRESSION_H
#define AST_TERNARY_EXPRESSION_H

#include <iostream>

#include "../Expression.hpp"

class TernaryExpression : public Expression {

public:
	Expression* condition;
	Expression* true_branch;
	Expression* false_branch;

	TernaryExpression(Expression* condition, Expression* t, Expression* f);

	virtual void Debug(std::ostream& dst, int indent) const;
	virtual Type GetType(VariableMap& bindings) const;
};

#endif
