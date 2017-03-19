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

std::string TernaryExpression::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	std::string if_label = unique("if");
	stack[if_label + "_res"] = GetType(bindings);
	out.push_back(new LabelInstruction(if_label + "_begin"));					// if_begin:
	std::string cond_res = condition->MakeIR(bindings, stack, out);				// condition
	out.push_back(new GotoIfEqualInstruction(if_label + "_false", cond_res, 0)); // beqz if_false
	out.push_back(new LabelInstruction(if_label + "_true"));					// if_true:
	std::string t_res = true_branch->MakeIR(bindings, stack, out);				// true_branch
	out.push_back(new MoveInstruction(if_label + "_res", t_res));				// move to result
	out.push_back(new GotoInstruction(if_label + "_end"));						// goto if_end
	out.push_back(new LabelInstruction(if_label + "_false"));					// if_false:
	std::string f_res = false_branch->MakeIR(bindings, stack, out);				// false_branch
	out.push_back(new MoveInstruction(if_label + "_res", f_res));				// move to result
	out.push_back(new LabelInstruction(if_label + "_end"));						// if_end:
	return if_label + "_res";
}

std::string TernaryExpression::MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	throw compile_error("cannot use ternary operators within an l-value", sourceFile, sourceLine);
}

int32_t TernaryExpression::evaluate_int(VariableMap const& bindings) const {
	if(condition->evaluate_int(bindings)) {
		return true_branch->evaluate_int(bindings);
	} else {
		return false_branch->evaluate_int(bindings);
	}
}
