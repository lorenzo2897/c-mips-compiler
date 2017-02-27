#ifndef AST_PROGRAMROOT_H
#define AST_PROGRAMROOT_H

#include <iostream>
#include <vector>

#include "Node.hpp"
#include "Scope.hpp"
#include "Declaration.hpp"
#include "Function.hpp"

class ProgramRoot : public Scope {

protected:
	std::vector<Function*> functions;

public:
	virtual void Debug(std::ostream& dst, int indent) const;
	virtual void PrintXML(std::ostream& dst, int indent) const;
	void add(Node* node);
};

#endif
