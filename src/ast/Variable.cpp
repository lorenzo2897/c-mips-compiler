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
	} else if(enums().value_exists(identifier)) {
		return Type("int", 0);
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
	} else if(enums().value_exists(identifier)) {
		int32_t signed_val = enums().get_value(identifier);
		uint32_t unsigned_val = *((uint32_t*) &signed_val);
		std::string name = unique((std::string)"enum_" + identifier + "_");
		stack[name] = GetType(bindings);
		out.push_back(new ConstantInstruction(name, GetType(bindings), unsigned_val));
		return name;
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
	if(enums().value_exists(identifier)) {
		return enums().get_value(identifier);
	}
	throw compile_error("variable " + identifier + " cannot be used within a constant expression", sourceFile, sourceLine);
}
