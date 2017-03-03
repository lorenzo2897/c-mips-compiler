#ifndef AST_UNARY_EXPRESSION_H
#define AST_UNARY_EXPRESSION_H

#include <iostream>
#include <vector>

#include "../Expression.hpp"
#include "../Value.hpp"

class UnaryExpression : public Expression {
public:
	enum UnaryOperator {
		op_preincrement,
		op_postincrement,
		op_predecrement,
		op_postdecrement,
		op_positive,
		op_negative,
		op_addressof,
		op_dereference,
		op_bitwisenot,
		op_logicalnot,
		op_sizeof
	};

	static Node* compute_sizeof_type(std::vector<std::string>* specifiers);

	UnaryExpression(Expression* expression, UnaryOperator op);
	UnaryExpression(Expression* expression, char op);

	Expression* expression;
	UnaryOperator op;

	virtual void Debug(std::ostream& dst, int indent) const;
	virtual Type GetType(VariableMap& bindings) const;
};

#endif
