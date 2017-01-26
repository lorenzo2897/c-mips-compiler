#ifndef AST_CAST_EXPRESSION_H
#define AST_CAST_EXPRESSION_H

#include <iostream>

#include "../Expression.hpp"

class CastExpression : public Expression {

public:
	std::string cast_type;
	int pointer_depth;
	Expression* rvalue;

	CastExpression();
	CastExpression(std::string cast_type, int pointer_depth, Expression* expression);

	virtual void Debug(std::ostream& dst, int indent) const;
};

#endif
