#ifndef AST_NODE_H
#define AST_NODE_H

#include <iostream>
#include <string>

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
