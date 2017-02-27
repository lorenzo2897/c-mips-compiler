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
