#include "TernaryExpression.hpp"

TernaryExpression::TernaryExpression(Expression* condition, Expression* t, Expression* f) : Expression(), condition(condition), true_branch(t), false_branch(f) {}

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

	if(a.is_compatible(b)) {
		return a;
	} else {
		throw compile_error("ternary expression has incompatible types", sourceFile, sourceLine);
	}
}

std::string TernaryExpression::MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	throw compile_error("cannot use ternary operators within an l-value", sourceFile, sourceLine);
}
