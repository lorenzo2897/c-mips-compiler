#include "BreakStatement.hpp"

BreakStatement::BreakStatement() : Statement(), is_continue(false) {}
BreakStatement::BreakStatement(bool is_continue) : Statement(), is_continue(is_continue) {}

void BreakStatement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << (is_continue ? "continue" : "break");
}
