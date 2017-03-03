#ifndef AST_NODE_H
#define AST_NODE_H

#include <iostream>
#include <string>

#include "../intrep/VariableMap.hpp"
#include "../intrep/Instruction.hpp"
#include "../intrep/UniqueNames.hpp"
#include "../CompileError.hpp"

class Node {

protected:
	std::string debug_extras;
	std::string spaces(int n) const;

public:
	Node() {}
	Node(std::string s) : debug_extras(s) {}
	virtual void PrettyPrint(std::ostream& dst, int indent) const;
	virtual void PrintXML(std::ostream& dst, int indent) const;
	virtual void Debug(std::ostream& dst, int indent) const = 0;

};

#endif
