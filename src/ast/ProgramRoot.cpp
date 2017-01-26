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
