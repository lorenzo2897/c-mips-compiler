#include "VariableMap.hpp"

#include "../ast/Declaration.hpp"
#include "../ast/Scope.hpp"

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

bool StructureType::member_exists(std::string name) const {
	for(std::vector<std::string>::const_iterator itr = order.begin(); itr != order.end(); ++itr) {
		if(*itr == name) {
			return true;
		}
	}
	return false;
}

Type StructureType::get_member_type(std::string name) const {
	if(members.count(name)) {
		return members.at(name);
	} else if(arrays.count(name)) {
		return arrays.at(name).type.addressof();
	} else {
		throw compile_error((std::string)"struct or union does not have a member named '" + name + "'");
	}
}

unsigned StructureType::get_member_offset(std::string name) const {
	std::vector<std::string>::const_iterator end = std::find(order.begin(), order.end(), name);
	if(end == order.end()) {
		throw compile_error((std::string)"struct or union does not have a member named '" + name + "'");
	}
	// look through vector adding up byte totals
	unsigned sum = 0;
	for(std::vector<std::string>::const_iterator itr = order.begin(); itr != end; ++itr) {
		if(members.count(*itr)) {
			sum += members.at(*itr).bytes();
		} else if(arrays.count(*itr)) {
			sum += arrays.at(*itr).total_size();
		}
	}
	return sum;
}

void StructureType::add_members(Scope *scope) {
	for(std::vector<Declaration*>::const_iterator itr = scope->declarations.begin(); itr != scope->declarations.end(); ++itr) {
		std::string name = (*itr)->identifier;
		if (member_exists(name)) {
			throw compile_error("cannot declare two elements of the name " + name + " in struct");
		}
		order.push_back(name);
		if((*itr)->is_array()) {
			arrays[name] = ArrayType((*itr)->var_type.dereference(), (*itr)->array_elements);
		} else {
			members[name] = (*itr)->var_type;
		}
	}
}

void StructureType::Debug(std::ostream& dst) const {
	for(std::vector<std::string>::const_iterator itr = order.begin(); itr != order.end(); ++itr) {
		if(members.count(*itr)) {
			dst << "    " << members.at(*itr).name() << " " << *itr << std::endl;
		} else if(arrays.count(*itr)) {
			dst << "    " << arrays.at(*itr).type.name() << " [" << arrays.at(*itr).elements << "] " << *itr << std::endl;
		}
	}
}

// **********************************

StructureMap _structures;

StructureMap structures() {
	return _structures;
}

unsigned struct_total_size(std::string name) {
	if(structures().count(name)) {
		return structures().at(name).total_size();
	} else {
		throw compile_error("struct " + name + " does not exist");
	}
}

void StructureMap::add(std::string name, StructureType s) {
	if(_structures.count(name)) {
		throw compile_error("a struct named " + name + " already exists");
	}
	_structures[name] = s;
}
void StructureMap::print(std::ostream& dst) {
	for(const_iterator itr = begin(); itr != end(); ++itr) {
		dst << "  struct " << itr->first << " {" << std::endl;
		itr->second.Debug(dst);
		dst << "  };" << std::endl;
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
