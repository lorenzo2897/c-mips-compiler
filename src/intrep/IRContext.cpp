#include "IRContext.hpp"
#include "../CompileError.hpp"

#include <sstream>

IRContext::IRContext(VariableMap const& globals, FunctionStack const& stack, std::map<std::string, unsigned> const& stack_offsets, std::string func_name)
: globals(globals), stack(stack), stack_offsets(stack_offsets), func_name(func_name) {}

bool IRContext::is_global(std::string name) const {
	return (globals.count(name));
}

unsigned IRContext::get_stack_offset(std::string name) const {
	if(stack_offsets.count(name)) {
		return stack_offsets.at(name);
	} else {
		throw compile_error((std::string)"IR: variable " + name + " not found in stack mapping");
	}
}

Type IRContext::get_type(std::string name) const {
	if(stack.count(name)) {
		return stack.at(name);
	} else if(globals.count(name)) {
		return globals.at(name).type;
	} else {
		throw compile_error((std::string)"IR: variable " + name + " not found in stack or globals");
	}
}

std::string IRContext::get_variable_address(std::string name) const {
	if(is_global(name)) {
		return name;
	} else {
		std::stringstream ss;
		ss << get_stack_offset(name) << "($fp)";
		return ss.str();
	}
}

std::string IRContext::get_return_label() const {
	return (std::string)"fnc_" + func_name + "_return";
}
