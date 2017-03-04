#ifndef AST_ARRAY_ACCESS_H
#define AST_ARRAY_ACCESS_H

#include <iostream>

#include "../Expression.hpp"

class ArrayAccess : public Expression {
public:
	Expression* array_base;
	Expression* array_index;

	ArrayAccess(Expression* base, Expression* index);

	virtual void Debug(std::ostream& dst, int indent) const;

	virtual Type GetType(VariableMap const& bindings) const;
};

#endif
