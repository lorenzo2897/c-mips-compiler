#include "Expression.hpp"

void Expression::Debug(std::ostream& dst, int indent) const {
	dst << "(undefined expression)";
}



void CompoundExpression::Debug(std::ostream& dst, int indent) const {
	dst << "(";
	for(std::vector<Expression*>::const_iterator itr = expressions.begin(); itr != expressions.end(); ++itr) {
		if(itr != expressions.begin()) {
			dst << ", ";
		}
		(*itr)->Debug(dst, indent);
	}
	dst << ")";
}

CompoundExpression::CompoundExpression(Expression* e) {
	expressions.push_back(e);
}

void CompoundExpression::add_expression(Expression *e) {
	expressions.push_back(e);
}
