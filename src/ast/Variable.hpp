#ifndef AST_VARIABLE_H
#define AST_VARIABLE_H

#include <string>

#include "Node.hpp"
#include "Expression.hpp"

class Variable : public Expression {

public:
	std::string identifier;

	Variable(std::string id);

	virtual void Debug(std::ostream& dst, int indent) const;
	virtual Type GetType(VariableMap& bindings) const;

};


#endif
