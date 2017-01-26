#include "AssignmentExpression.hpp"

AssignmentExpression::AssignmentExpression(Expression* l, Expression* r, char assignment_type) : lvalue(l), rvalue(r), assignment_type(assignment_type) {}

void AssignmentExpression::Debug(std::ostream& dst, int indent) const {
	dst << "(";
	lvalue->Debug(dst, indent);
	if(assignment_type == '=') {
		dst << " = ";
	} else {
		dst << " " << assignment_type << "= ";
	}
	rvalue->Debug(dst, indent);
	dst << ")";
}
