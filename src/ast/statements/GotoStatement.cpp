#include "GotoStatement.hpp"

GotoStatement::GotoStatement() : Statement() {}
GotoStatement::GotoStatement(std::string label) : Statement(), label(label) {}

void GotoStatement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "goto " << label;
}

void GotoStatement::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	out.push_back(new GotoInstruction(label));
}
