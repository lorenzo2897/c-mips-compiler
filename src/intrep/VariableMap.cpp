#include "VariableMap.hpp"

#include "../ast/Declaration.hpp"

// **********************************

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
			unique("var_" + (*itr)->identifier + "_"),
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
		} else {
			throw compile_error("could not find local variable " + (*itr)->identifier + " in the bindings");
		}
	}
}
