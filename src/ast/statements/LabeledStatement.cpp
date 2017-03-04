#include "LabeledStatement.hpp"

/* ************************* */

LabeledStatement::LabeledStatement() : Statement(), statement(NULL) {}
LabeledStatement::LabeledStatement(std::string label, Statement* s) : Statement(), label(label), statement(s) {}

void LabeledStatement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent>=2 ? indent-2 : indent) << "Label " << label << ": ";
	if(statement) {
		statement->Debug(dst, indent);
	} else {
		dst << " (null statement!)";
	}
}

void LabeledStatement::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	out.push_back(new LabelInstruction(label));
	if(statement) {
		statement->MakeIR(bindings, stack, out);
	}
}
