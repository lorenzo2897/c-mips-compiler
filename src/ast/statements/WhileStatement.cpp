#include "WhileStatement.hpp"

/* ************************* */

WhileStatement::WhileStatement() : Statement(), expression(NULL), statement(NULL), statement_before_condition(false) {}
WhileStatement::WhileStatement(Expression* e, Statement* s, bool statement_before_condition) : Statement(), expression(e), statement(s), statement_before_condition(statement_before_condition) {}

void WhileStatement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << (statement_before_condition ? "do_while (" : "while (");
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

void WhileStatement::PrintXML(std::ostream& dst, int indent) const {
	if(statement) statement->PrintXML(dst, indent);
}
