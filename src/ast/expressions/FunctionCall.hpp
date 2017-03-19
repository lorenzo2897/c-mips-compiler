#ifndef AST_FUNCTION_CALL_H
#define AST_FUNCTION_CALL_H

#include <iostream>
#include <vector>

#include "../Expression.hpp"

class FunctionCall : public Expression {
public:
	std::string function_name;
	std::vector<Expression*> args;

	FunctionCall(std::string function_name);
	FunctionCall(std::string function_name, std::vector<Expression*> args);

	virtual void Debug(std::ostream& dst, int indent) const;
	virtual Type GetType(VariableMap const& bindings) const;

	virtual std::string MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const;
	virtual std::string MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const;
};

#endif
