#include "SwitchStatement.hpp"

/* ************************* */

SwitchStatement::SwitchStatement() : Statement(), expression(NULL), statement(NULL) {}
SwitchStatement::SwitchStatement(Expression* e, Statement* s) : Statement(), expression(e), statement(s) {}

void SwitchStatement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "switch(";
	if(expression)
		expression->Debug(dst, indent);
	else
		dst << "null expression";
	dst << ")";
	if(statement) {
		statement->Debug(dst, indent);
	} else {
		dst << " (null statement!)";
	}
}
