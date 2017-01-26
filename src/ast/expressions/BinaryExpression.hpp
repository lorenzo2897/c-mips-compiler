#ifndef AST_BINARY_EXPRESSION_H
#define AST_BINARY_EXPRESSION_H

#include <iostream>

#include "../Expression.hpp"

class BinaryExpression : public Expression {

public:
	enum BinaryOperator {
		op_logicalor,
		op_logicaland,
		op_bitwiseor,
		op_bitwisexor,
		op_bitwiseand,
		op_equals,
		op_notequals,
		op_lessthan,
		op_morethan,
		op_lessequal,
		op_moreequal,
		op_leftshift,
		op_rightshift,
		op_add,
		op_subtract,
		op_multiply,
		op_divide,
		op_modulo
	};

	Expression* left;
	Expression* right;
	BinaryOperator op;

	BinaryExpression(Expression* l, Expression* r, BinaryOperator op);

	virtual void Debug(std::ostream& dst, int indent) const;
};

#endif
