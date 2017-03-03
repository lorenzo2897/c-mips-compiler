#include "Variable.hpp"

Variable::Variable(std::string id) {
	identifier = id;
}

void Variable::Debug(std::ostream& dst, int indent) const {
	dst << identifier;
}

Type Variable::GetType(VariableMap& bindings) const {
	if(bindings.count(identifier)) {
		return bindings.at(identifier).type;
	} else {
		throw compile_error("variable " + identifier + " was not found in this scope");
	}
}
