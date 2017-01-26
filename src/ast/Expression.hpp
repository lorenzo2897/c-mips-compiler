#ifndef AST_EXPRESSION_H
#define AST_EXPRESSION_H

#include <iostream>
#include <vector>

#include "Node.hpp"

class Expression : public Node {

public:
	virtual void Debug(std::ostream& dst, int indent) const;

};

/* ************************* */

class CompoundExpression : public Expression {
public:
	std::vector<Expression*> expressions;

	CompoundExpression(Expression* e);

	virtual void Debug(std::ostream& dst, int indent) const;
	void add_expression(Expression* e);
};

#endif
