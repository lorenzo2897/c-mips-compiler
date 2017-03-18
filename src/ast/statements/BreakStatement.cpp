#include "BreakStatement.hpp"

BreakStatement::BreakStatement() : Statement(), is_continue(false) {}
BreakStatement::BreakStatement(bool is_continue) : Statement(), is_continue(is_continue) {}

void BreakStatement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << (is_continue ? "continue" : "break");
}

void BreakStatement::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	if(is_continue) {
		if(bindings.continue_destination == "") {
			throw compile_error("'continue' statement not in loop statement", sourceFile, sourceLine);
		} else {
			out.push_back(new GotoInstruction(bindings.continue_destination));
		}
	} else {
		if(bindings.break_destination == "") {
			throw compile_error("'break' statement not in loop or switch statement", sourceFile, sourceLine);
		} else {
			out.push_back(new GotoInstruction(bindings.break_destination));
		}
	}
}
