#ifndef AST_DECLARATION_H
#define AST_DECLARATION_H

#include <iostream>
#include <string>
#include <vector>

#include "Node.hpp"
#include "Expression.hpp"

class Declaration : public Node {

protected:

public:
	Declaration();

	Type var_type;
	unsigned array_elements;
	std::string identifier;
	Expression* initialiser;

	bool is_array() const;

	void MakeIR_initialisers(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const;

	virtual void Debug(std::ostream& dst, int indent) const;
	virtual void PrintXML(std::ostream& dst, int indent) const;
};

#endif
