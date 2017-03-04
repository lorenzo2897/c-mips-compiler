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

Type TernaryExpression::GetType(VariableMap const& bindings) const {
	Type a = true_branch->GetType(bindings);
	Type b = false_branch->GetType(bindings);

	if(a.equals(b)) {
		return a;
	} else {
		throw compile_error("ternary expression has different types");
	}
}
