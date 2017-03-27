#include "ProgramRoot.hpp"

#include <cstdio>

void ProgramRoot::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "Program Root!";

	dst << std::endl << spaces(indent) << "Structures: " << std::endl;
	structures().print(dst);
	dst << std::endl << spaces(indent) << "Enumerations: " << std::endl;
	enums().print(dst);
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

// *******************************************************

void ProgramRoot::populate_declarations(VariableMap& bindings, ArrayMap& arrays) const {
	for(std::vector<Declaration*>::const_iterator itr = declarations.begin(); itr != declarations.end(); ++itr) {
		if(bindings.count((*itr)->identifier)) {
			throw compile_error("global variable " + (*itr)->identifier + " was declared twice");
		}
		bindings[(*itr)->identifier] = Binding((*itr)->identifier, (*itr)->var_type, true);
		if((*itr)->is_array()) {
			arrays[(*itr)->identifier] = ArrayType((*itr)->var_type.dereference(), (*itr)->array_elements);
		}
	}
}

void ProgramRoot::populate_functions(VariableMap& bindings) const {
	for(std::vector<Function*>::const_iterator itr = functions.begin(); itr != functions.end(); ++itr) {
		if(bindings.count((*itr)->function_name)) {
			throw compile_error("function " + (*itr)->function_name + " conflicts with another declaration of the same name");
		}
		// build a list of function parameters
		std::vector<Type> params;
		for(std::vector<Declaration*>::const_iterator p = (*itr)->parameters.begin(); p != (*itr)->parameters.end(); ++p) {
			params.push_back((*p)->var_type);
		}
		bindings[(*itr)->function_name] = Binding((*itr)->function_name, (*itr)->return_type, params);
	}
}

void ProgramRoot::CompileIR(std::ostream &dst) const {
	dst << std::endl << "# Intermediate representation generated using lscc" << std::endl << std::endl;

	VariableMap global_bindings;
	ArrayMap arrays;

	// populate map with global varaibles
	populate_declarations(global_bindings, arrays);

	// generate labels for global variables
	dst << "# Global structs" << std::endl;
	structures().print(dst);
	dst << "# Global enums" << std::endl;
	enums().print(dst);
	dst << "# Global arrays" << std::endl;
	for(ArrayMap::const_iterator itr = arrays.begin(); itr != arrays.end(); ++itr) {
		dst << (*itr).first << ": (" << (*itr).second.total_size() << ") " << (*itr).second.type.name() << " [" << (*itr).second.elements << "]" << std::endl;
	}
	dst << "# Global variables" << std::endl;
	for(VariableMap::const_iterator itr = global_bindings.begin(); itr != global_bindings.end(); ++itr) {
		dst << (*itr).second.alias << ": (" << (*itr).second.type.bytes() << ") " << (*itr).second.type.name() << std::endl;
	}

	// populate map with function names
	populate_functions(global_bindings);

	// generate code for every function
	dst << std::endl;
	dst << "# Functions" << std::endl << std::endl;
	for(std::vector<Function*>::const_iterator itr = functions.begin(); itr != functions.end(); ++itr) {
		(*itr)->CompileIR(global_bindings, dst);
	}
}


void ProgramRoot::CompileMIPS(std::ostream &dst) const {
	dst << std::endl << "# MIPS assembly generated using lscc" << std::endl << std::endl;

	VariableMap global_bindings;
	ArrayMap arrays;

	populate_declarations(global_bindings, arrays);

	// output global variables

	dst << ".data\n\n";

	for(ArrayMap::const_iterator itr = arrays.begin(); itr != arrays.end(); ++itr) {
		dst << "    .globl " << (*itr).first << "_arr\n    .align 4\n";
		dst << "  " << (*itr).first << "_arr:\n    .space " << (*itr).second.total_size() << "\n\n";
	}

	for(VariableMap::const_iterator itr = global_bindings.begin(); itr != global_bindings.end(); ++itr) {
		if(arrays.count((*itr).second.alias)) {
			dst << "    .globl " << (*itr).second.alias << "\n    .align 4\n";
			dst << "  " << (*itr).second.alias << ":\n    .word " << (*itr).second.alias << "_arr\n\n";
		} else {
			dst << "    .globl " << (*itr).second.alias << "\n    .align 4\n";
			// initialise global vars
			if((*itr).second.type.is_integer()) {
				bool initialised = false;
				for(std::vector<Declaration*>::const_iterator di = declarations.begin(); di != declarations.end(); ++di) {
					if((*di)->identifier == (*itr).first) {
						if((*di)->initialiser != NULL) {
							initialised = true;
							int val;
							try {
								val = (*di)->initialiser->evaluate_int(global_bindings);
							} catch (compile_error e) {
								val = 0;
							}
							if((*itr).second.type.bytes() == 1) {
								dst << "  " << (*itr).second.alias << ":\n    .byte " << (int8_t)val << "\n\n";
							} else if((*itr).second.type.bytes() == 2) {
								dst << "  " << (*itr).second.alias << ":\n    .half " << (int16_t)val << "\n\n";
							} else {
								dst << "  " << (*itr).second.alias << ":\n    .word " << val << "\n\n";
							}
							break;
						}
					}
				}
				if(!initialised) {
					dst << "  " << (*itr).second.alias << ":\n    .space " << (*itr).second.type.bytes() << "\n\n";
				}
			} else {
				dst << "  " << (*itr).second.alias << ":\n    .space " << (*itr).second.type.bytes() << "\n\n";
			}
		}
	}

	populate_functions(global_bindings);

	// generate code for every function
	dst << std::endl;
	dst << ".text\n\n";
	for(std::vector<Function*>::const_iterator itr = functions.begin(); itr != functions.end(); ++itr) {
		(*itr)->CompileMIPS(global_bindings, dst);
	}

}
