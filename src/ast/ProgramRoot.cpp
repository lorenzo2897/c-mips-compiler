#include "ProgramRoot.hpp"

#include <cstdio>

void ProgramRoot::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "Program Root!";

	dst << std::endl << spaces(indent) << "Declarations: " << std::endl;
	for(std::vector<Declaration*>::const_iterator itr = declarations.begin(); itr != declarations.end(); ++itr) {
		(*itr)->Debug(dst, indent+2);
	}
	dst << std::endl << spaces(indent) << "Functions: ";
	for(std::vector<Function*>::const_iterator itr = functions.begin(); itr != functions.end(); ++itr) {
		(*itr)->Debug(dst, indent+2);
	}
}

void ProgramRoot::PrintXML(std::ostream& dst, int indent) const {
	dst << std::endl << std::endl << spaces(indent) << "<?xml version=\"1.0\"?>" << std::endl;
	dst << spaces(indent) << "<Program>" << std::endl;
	for(std::vector<Declaration*>::const_iterator itr = declarations.begin(); itr != declarations.end(); ++itr) {
		(*itr)->PrintXML(dst, indent+2);
	}
	for(std::vector<Function*>::const_iterator itr = functions.begin(); itr != functions.end(); ++itr) {
		(*itr)->PrintXML(dst, indent+2);
	}
	dst << spaces(indent) << "</Program>" << std::endl;
}

void ProgramRoot::add(Node* node) {
	if(node == NULL) {
		//fprintf(stderr, "warning: program root did not add item because pointer is null\n");
		return;
	}

	Function* function = dynamic_cast<Function*>(node);
	Scope* scope = dynamic_cast<Scope*>(node);
	if(function) {
		functions.push_back(function);
	} else if(scope) {
		declarations.insert(declarations.end(), scope->declarations.begin(), scope->declarations.end());
	} else {
		fprintf(stderr, "warning: program root did not add item because idk what it is\n");
	}
}

void ProgramRoot::CompileIR(std::ostream &dst) const {
	dst << std::endl << "# Intermediate representation generated using lscc" << std::endl << std::endl;

	VariableMap bindings;

	// populate map with global varaibles
	for(std::vector<Declaration*>::const_iterator itr = declarations.begin(); itr != declarations.end(); ++itr) {
		if(bindings.count((*itr)->identifier)) {
			throw compile_error("global variable " + (*itr)->identifier + " was declared twice");
		}
		Binding b;
		b.alias = (*itr)->identifier;
		b.type = (*itr)->var_type;
		b.is_global = true;
		bindings[(*itr)->identifier] = b;
	}

	// generate labels for variables
	dst << "# Global variables" << std::endl;
	for(VariableMap::const_iterator itr = bindings.begin(); itr != bindings.end(); ++itr) {
		dst << (*itr).first << ": (" << (*itr).second.type.bytes() << ") " << (*itr).second.type.name() << std::endl;
	}

	// populate map with function names
	for(std::vector<Function*>::const_iterator itr = functions.begin(); itr != functions.end(); ++itr) {
		if(bindings.count((*itr)->function_name)) {
			throw compile_error("function " + (*itr)->function_name + " conflicts with another declaration of the same name");
		}
		Binding b;
		b.alias = (*itr)->function_name;
		b.type = (*itr)->return_type;
		b.is_global = true;
		bindings[(*itr)->function_name] = b;
	}

	dst << std::endl;
	dst << "# Functions" << std::endl << std::endl;
	// generate code for every function
	for(std::vector<Function*>::const_iterator itr = functions.begin(); itr != functions.end(); ++itr) {
		(*itr)->CompileIR(bindings, dst);
	}
}
