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
		if(bindings.at(identifier).is_function) {
			throw compile_error("identifier " + identifier + " is a function, not a variable", sourceFile, sourceLine);
		} else {
			return bindings.at(identifier).alias;
		}
	} else {
		throw compile_error("variable " + identifier + " was not found in this scope", sourceFile, sourceLine);
	}
}

std::string Variable::MakeIR_lvalue(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	std::string s = MakeIR(bindings, stack, out);
	std::string r = unique((std::string)"addr_" + identifier + "_");
	stack[r] = GetType(bindings).addressof();
	out.push_back(new AddressOfInstruction(r, s));
	return r;
}

int32_t Variable::evaluate_int(VariableMap const& bindings) const {
	throw compile_error("variable " + identifier + " cannot be used within a constant expression", sourceFile, sourceLine);
}
