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

	std::vector<std::string> specifiers;
	int pointer_depth;
	std::string identifier;
	Expression* initialiser;
	virtual void Debug(std::ostream& dst, int indent) const;
};

#endif
