#include "TernaryExpression.hpp"

TernaryExpression::TernaryExpression(Expression* condition, Expression* t, Expression* f) : condition(condition), true_branch(t), false_branch(f) {}

void TernaryExpression::Debug(std::ostream& dst, int indent) const {
	dst << "(";
	condition->Debug(dst, indent);
	dst << " ? ";
	true_branch->Debug(dst, indent);
	dst << " : ";
	false_branch->Debug(dst, indent);
	dst << ")";
}
