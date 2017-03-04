#ifndef AST_ASSIGNMENT_EXPRESSION_H
#define AST_ASSIGNMENT_EXPRESSION_H

#include <iostream>

#include "../Expression.hpp"

class AssignmentExpression : public Expression {

public:
	Expression* lvalue;
	Expression* rvalue;
	char assignment_type;

	AssignmentExpression(Expression* l, Expression* r, char assignment_type);

	virtual void Debug(std::ostream& dst, int indent) const;
	virtual Type GetType(VariableMap const& bindings) const;
};

#endif
