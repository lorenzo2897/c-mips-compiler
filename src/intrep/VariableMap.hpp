#ifndef IR_VARIABLE_MAP_H
#define IR_VARIABLE_MAP_H

#include <map>

#include "Type.hpp"

struct Binding {
	std::string alias;
	Type type;
	bool is_global;
};

// **********************************

class Declaration;

class VariableMap : public std::map<std::string, Binding> {
public:
	void add_bindings(std::vector<Declaration*> const& declarations);
};


// **********************************

class FunctionStack : public std::map<std::string, Type> {
public:
	void add_variables(VariableMap const& aliases, std::vector<Declaration*> const& declarations);
};


#endif
