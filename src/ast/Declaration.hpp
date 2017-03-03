#ifndef AST_DECLARATION_H
#define AST_DECLARATION_H

#include <iostream>
#include <string>
#include <vector>

#include "Node.hpp"
#include "Expression.hpp"

#include "../intrep/Type.hpp"

class Declaration : public Node {

protected:

public:
	Declaration();

	Type var_type;
	std::string identifier;
	Expression* initialiser;

	virtual void Debug(std::ostream& dst, int indent) const;
	virtual void PrintXML(std::ostream& dst, int indent) const;
};

#endif
