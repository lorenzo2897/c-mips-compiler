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
};

#endif
