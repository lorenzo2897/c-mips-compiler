#include "VariableMap.hpp"

#include "../ast/Declaration.hpp"

// **********************************

VariableMap::VariableMap() : break_destination(""), continue_destination(""), std::map<std::string, Binding>() {}

void VariableMap::add_bindings(std::vector<Declaration*> const& declarations) {
	// check if there are any conflicting names in the current list
	{
		std::map<std::string, int> v;
		for(std::vector<Declaration*>::const_iterator itr = declarations.begin(); itr != declarations.end(); ++itr) {
			if(v.count((*itr)->identifier)) {
				throw compile_error("cannot redeclare variable " + (*itr)->identifier + " in the same scope");
			} else {
				v[(*itr)->identifier] = 1;
			}
		}
	}

	// add all of the declarations, shadowing any previous version
	for(std::vector<Declaration*>::const_iterator itr = declarations.begin(); itr != declarations.end(); ++itr) {
		Binding b(
			(*itr)->is_array()
				? unique("arr_" + (*itr)->identifier + "_")
				: unique("var_" + (*itr)->identifier + "_"),
			(*itr)->var_type,
			false
		);
		(*this)[(*itr)->identifier] = b;
	}
}

// **********************************

void FunctionStack::add_variables(VariableMap const& aliases, std::vector<Declaration*> const& declarations) {
	// add all declarations to the stack by their corresponding aliases
	for(std::vector<Declaration*>::const_iterator itr = declarations.begin(); itr != declarations.end(); ++itr) {
		if(aliases.count((*itr)->identifier)) {
			std::string a = aliases.at((*itr)->identifier).alias;
			(*this)[a] = (*itr)->var_type;
			if((*itr)->is_array()) {
				if(!(*itr)->var_type.is_pointer()) {
					throw compile_error("variable " + (*itr)->identifier + " is not a pointer and cannot be used as array");
				}
				arrays[a] = ArrayType((*itr)->var_type.dereference(), (*itr)->array_elements);
			}
		} else {
			throw compile_error("could not find local variable " + (*itr)->identifier + " in the bindings");
		}
	}
}
