#include "Variable.hpp"

Variable::Variable(std::string id) : Expression() {
	identifier = id;
}

void Variable::Debug(std::ostream& dst, int indent) const {
	dst << identifier;
}

Type Variable::GetType(VariableMap const& bindings) const {
	if(bindings.count(identifier)) {
		return bindings.at(identifier).type;
	} else {
		throw compile_error("variable " + identifier + " was not found in this scope", sourceFile, sourceLine);
	}
}

std::string Variable::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	if(bindings.count(identifier)) {
		return bindings.at(identifier).alias;
	} else {
		throw compile_error("variable " + identifier + " was not found in this scope", sourceFile, sourceLine);
	}
}
