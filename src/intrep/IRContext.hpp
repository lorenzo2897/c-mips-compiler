#ifndef IR_CONTEXT_H
#define IR_CONTEXT_H

#include "VariableMap.hpp"

class IRContext {
	// globals, local stack, and function declarations
	VariableMap globals;
	FunctionStack stack;
	// stack mappings
	std::map<std::string, unsigned> stack_offsets;
	// return label
	std::string func_name;
public:
	IRContext(VariableMap const& globals, FunctionStack const& stack, std::map<std::string, unsigned> const& stack_offsets, std::string func_name);

	bool is_global(std::string name) const;
	unsigned get_stack_offset(std::string name) const;
	Type get_type(std::string name) const;
	std::string get_variable_address(std::string name) const;
	std::string get_return_label() const;
};

#endif
