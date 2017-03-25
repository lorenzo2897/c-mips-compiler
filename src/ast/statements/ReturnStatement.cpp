#include "ReturnStatement.hpp"

ReturnStatement::ReturnStatement() : Statement(), expression(NULL) {}
ReturnStatement::ReturnStatement(Expression* e) : Statement(), expression(e) {}

void ReturnStatement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "return ";
	if(expression)
		expression->Debug(dst, indent);
}

void ReturnStatement::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	if(expression) {
		std::string res = expression->MakeIR(bindings, stack, out);
		out.push_back(new ReturnInstruction(res));
	} else {
		out.push_back(new ReturnInstruction());
	}
}
