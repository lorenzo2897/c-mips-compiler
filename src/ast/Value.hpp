#ifndef AST_VALUE_H
#define AST_VALUE_H

#include <iostream>
#include <stdint.h>

#include "Node.hpp"
#include "Expression.hpp"

class Value : public Expression {
public:
	enum ValueType {
		V_STRING,
		V_CHAR,
		V_INT,
		V_FLOAT,
		V_DOUBLE
	};

protected:
	ValueType type;

	union {
		char c;
		unsigned int i;
		float f;
		double d;
	} val;

	std::string strval;

public:
	Value(std::string s);
	Value(unsigned int i);
	Value(int i);
	Value(float f);
	Value(double d);
	Value(char c);

	virtual void Debug(std::ostream& dst, int indent) const;
	virtual Type GetType(VariableMap const& bindings) const;

	virtual std::string MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const;
};

#endif
