#ifndef AST_CAST_EXPRESSION_H
#define AST_CAST_EXPRESSION_H

#include <iostream>

#include "../Expression.hpp"

#include "../../intrep/Type.hpp"

class CastExpression : public Expression {

public:
	Type cast_type;
	Expression* rvalue;

	CastExpression();
	CastExpression(std::string cast_type, int pointer_depth, Expression* expression);

	virtual void Debug(std::ostream& dst, int indent) const;
	virtual Type GetType(VariableMap const& bindings) const;
};

#endif
