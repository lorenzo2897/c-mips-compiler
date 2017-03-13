#include "AssignmentExpression.hpp"

AssignmentExpression::AssignmentExpression(Expression* l, Expression* r, char assignment_type) : lvalue(l), rvalue(r), assignment_type(assignment_type) {}

void AssignmentExpression::Debug(std::ostream& dst, int indent) const {
	dst << "(";
	lvalue->Debug(dst, indent);
	if(assignment_type == '=') {
		dst << " = ";
	} else {
		dst << " " << assignment_type << "= ";
	}
	rvalue->Debug(dst, indent);
	dst << ")";
}

Type AssignmentExpression::GetType(VariableMap const& bindings) const {
	return lvalue->GetType(bindings);
}

std::string AssignmentExpression::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	if(assignment_type == '=') {
		// evaluate the left hand side to get a pointer to the location to assign to
		std::string dst = lvalue->MakeIR_lvalue(bindings, stack, out);
		// evaluate the right hand side to get the value to assign
		std::string src = rvalue->MakeIR(bindings, stack, out);
		// output the assignment operation
		out.push_back(new AssignInstruction(dst, src));
		return src;
	} else {
		// TODO: implement unary assignment
		throw compile_error("unary assignment expressions not implemented");
	}
}

std::string AssignmentExpression::MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	throw compile_error("cannot use an assignment expression within an l-value");
}
