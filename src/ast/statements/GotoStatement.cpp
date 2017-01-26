#include "GotoStatement.hpp"

GotoStatement::GotoStatement() : Statement() {}
GotoStatement::GotoStatement(std::string label) : Statement(), label(label) {}

void GotoStatement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "goto " << label;
}
