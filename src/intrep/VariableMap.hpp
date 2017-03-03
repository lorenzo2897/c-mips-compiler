#include <map>

#include "Type.hpp"

struct Binding {
	std::string alias;
	Type type;
	bool is_global;
};

typedef std::map<std::string, Binding> VariableMap;
