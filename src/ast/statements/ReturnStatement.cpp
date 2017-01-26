#include "ReturnStatement.hpp"

ReturnStatement::ReturnStatement() : Statement(), expression(NULL) {}
ReturnStatement::ReturnStatement(Expression* e) : Statement(), expression(e) {}

void ReturnStatement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "return ";
	if(expression)
		expression->Debug(dst, indent);
}
