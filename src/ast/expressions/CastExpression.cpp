#include "CastExpression.hpp"

CastExpression::CastExpression() : pointer_depth(0), rvalue(NULL) {}

CastExpression::CastExpression(std::string cast_type, int pointer_depth, Expression* expression)
: cast_type(cast_type),
pointer_depth(pointer_depth),
rvalue(expression)
{}

void CastExpression::Debug(std::ostream& dst, int indent) const {
	dst << "((";
	dst << cast_type;
	for(int i = 0; i < pointer_depth; ++i) {
		dst << "*";
	}
	dst << ") ";
	rvalue->Debug(dst, indent);
	dst << ")";
}
