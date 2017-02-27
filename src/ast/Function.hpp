#ifndef AST_FUNCTION_H
#define AST_FUNCTION_H

#include <iostream>
#include <vector>

#include "Node.hpp"
#include "Scope.hpp"

class Function : public Scope {

protected:

public:
	Function();

	std::string function_name;
	std::vector<std::string> specifiers;
	int pointer_depth;
	std::vector<Declaration*> parameters;

	void merge_parameters(Scope* scope);

	virtual void Debug(std::ostream& dst, int indent) const;
	virtual void PrintXML(std::ostream& dst, int indent) const;
};

#endif
