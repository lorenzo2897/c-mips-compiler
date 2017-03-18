#include "IfStatement.hpp"

/* ************************* */

IfStatement::IfStatement() : Statement(), condition(NULL), true_body(NULL), false_body(NULL) {}
IfStatement::IfStatement(Expression* c, Statement* t, Statement* f) : Statement(), condition(c), true_body(t), false_body(f) {}

void IfStatement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "if (";
	if(condition)
		condition->Debug(dst, indent);
	else
		dst << "null expression";
	dst << ")";

	if(true_body) {
		true_body->Debug(dst, indent+2);
	} else {
		dst << " (null statement!)";
	}

	if(false_body) {
		dst << std::endl << spaces(indent) << "else";
		false_body->Debug(dst, indent+2);
	}
}

void IfStatement::PrintXML(std::ostream& dst, int indent) const {
	if(true_body) {
		true_body->PrintXML(dst, indent);
	}
	if(false_body) {
		false_body->PrintXML(dst, indent);
	}
}

void IfStatement::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	std::string if_label = unique("if");
	if(!condition) { throw compile_error("empty if condition"); }
	/*
	if_begin:
	  condition
	  beqz if_false
	if_true:
	  true_branch
	  goto if_end
	if_false:
	  false_branch
	if_end:
	*/
	out.push_back(new LabelInstruction(if_label + "_begin"));					// if_begin:
	std::string cond_res = condition->MakeIR(bindings, stack, out);				// condition
	out.push_back(new GotoIfEqualInstruction(if_label + "_false", cond_res, 0)); // beqz if_false
	out.push_back(new LabelInstruction(if_label + "_true"));					// if_true:
	if(true_body) true_body->MakeIR(bindings, stack, out);						// true_branch
	out.push_back(new GotoInstruction(if_label + "_end"));						// goto if_end
	out.push_back(new LabelInstruction(if_label + "_false"));					// if_false:
	if(false_body) false_body->MakeIR(bindings, stack, out);					// false_branch
	out.push_back(new LabelInstruction(if_label + "_end"));						// if_end:
}
