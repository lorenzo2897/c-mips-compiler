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
	// return value if struct or union
	Type return_type;
	unsigned return_struct_offset;

public:
	IRContext(VariableMap const& globals,
		FunctionStack const& stack,
		std::map<std::string, unsigned> const& stack_offsets,
		std::string func_name,
		Type return_type,
		unsigned return_struct_offset);

	// variables
	bool is_global(std::string name) const;
	unsigned get_stack_offset(std::string name) const;
	Type get_type(std::string name) const;
	std::vector<Type> get_function_parameters(std::string name) const;
	std::string get_variable_address(std::string name) const;
	// returns
	std::string get_return_label() const;
	Type get_return_type() const;
	unsigned get_return_struct_offset() const;


	// loading and storing
	void load_variable(std::ostream &out, std::string source, unsigned reg_number) const;
	void store_variable(std::ostream &out, std::string destination, unsigned reg_number) const;
	void copy(std::ostream &out, std::string source, std::string destination, unsigned total_bytes) const;

};

#endif
