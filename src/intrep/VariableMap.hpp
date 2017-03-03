#ifndef IR_VARIABLE_MAP_H
#define IR_VARIABLE_MAP_H

#include <map>

#include "Type.hpp"

struct Binding {
	std::string alias;
	Type type;
	bool is_global;
};

typedef std::map<std::string, Binding> VariableMap;

#endif
