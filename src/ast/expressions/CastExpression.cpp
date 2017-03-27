#include "CastExpression.hpp"

CastExpression::CastExpression() : Expression(), rvalue(NULL) {}

CastExpression::CastExpression(std::string cast_type, int pointer_depth, Expression* expression)
:
Expression(),
cast_type(Type(cast_type, pointer_depth)),
rvalue(expression)
{}

CastExpression::CastExpression(std::string cast_type1, std::string cast_type2, int pointer_depth, Expression* expression)
:
Expression(),
cast_type(Type(cast_type1, cast_type2, pointer_depth)),
rvalue(expression)
{}

void CastExpression::Debug(std::ostream& dst, int indent) const {
	dst << "((";
	dst << cast_type.name();
	dst << ") ";
	rvalue->Debug(dst, indent);
	dst << ")";
}

Type CastExpression::GetType(VariableMap const& bindings) const {
	return cast_type;
}

std::string CastExpression::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	std::string src = rvalue->MakeIR(bindings, stack, out);
	std::string dst = unique("cast");
	stack[dst] = GetType(bindings);
	out.push_back(new CastInstruction(dst, src, GetType(bindings)));
	return dst;
}

std::string CastExpression::MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	throw compile_error("cannot use cast within an l-value", sourceFile, sourceLine);
}
