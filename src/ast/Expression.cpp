#include "Expression.hpp"

#include <typeinfo>

Expression::Expression() : sourceFile(currentSourceFile), sourceLine(currentSourceLine) {}

void Expression::Debug(std::ostream& dst, int indent) const {
	dst << "(undefined expression)";
}

std::string Expression::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	throw compile_error((std::string)"assembly generation not implemented for " + typeid(*this).name());
}

/* ************************************************* */

void CompoundExpression::Debug(std::ostream& dst, int indent) const {
	dst << "(";
	for(std::vector<Expression*>::const_iterator itr = expressions.begin(); itr != expressions.end(); ++itr) {
		if(itr != expressions.begin()) {
			dst << ", ";
		}
		(*itr)->Debug(dst, indent);
	}
	dst << ")";
}

CompoundExpression::CompoundExpression(Expression* e) {
	expressions.push_back(e);
}

void CompoundExpression::add_expression(Expression *e) {
	expressions.push_back(e);
}

Type CompoundExpression::GetType(VariableMap const& bindings) const {
	if(expressions.size() == 0) {
		throw compile_error("getting type of empty CompoundExpression");
	}

	return expressions.at(expressions.size() - 1)->GetType(bindings);
}

std::string CompoundExpression::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	// execute each instruction in series and return the last value
	std::string res;
	for(std::vector<Expression*>::const_iterator itr = expressions.begin(); itr != expressions.end(); ++itr) {
		res = (*itr)->MakeIR(bindings, stack, out);
	}
	return res;
}
