#include "Function.hpp"

Function::Function() : Scope() {}

void Function::merge_parameters(Scope *scope) {
	parameters.insert(parameters.end(), scope->declarations.begin(), scope->declarations.end());
}

void Function::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "Function (" << function_name << ") type:";
	dst << return_type.name();

	dst << std::endl << spaces(indent) << "Parameters:" << std::endl;
	for(std::vector<Declaration*>::const_iterator itr = parameters.begin(); itr != parameters.end(); ++itr) {
		(*itr)->Debug(dst, indent+2);
	}

	dst << std::endl << spaces(indent) << "Declarations:" << std::endl;
	for(std::vector<Declaration*>::const_iterator itr = declarations.begin(); itr != declarations.end(); ++itr) {
		(*itr)->Debug(dst, indent+2);
	}

	if(statements.size() > 0) {
		dst << spaces(indent) << "Body: ";
		for(std::vector<Statement*>::const_iterator itr = statements.begin(); itr != statements.end(); ++itr) {
			(*itr)->Debug(dst, indent+2);
		}
	} else {
		dst << spaces(indent) << "Body: empty";
	}
	dst << std::endl << spaces(indent) << "End function " << function_name << std::endl;
}

void Function::PrintXML(std::ostream& dst, int indent) const {
	dst << spaces(indent) << "<Function id=\"" << function_name << "\">" << std::endl;

	for(std::vector<Declaration*>::const_iterator itr = parameters.begin(); itr != parameters.end(); ++itr) {
		dst << spaces(indent+2) << "<Parameter id=\"" << (*itr)->identifier << "\" />" << std::endl;
	}

	dst << spaces(indent+2) << "<Scope>" << std::endl;

	for(std::vector<Declaration*>::const_iterator itr = declarations.begin(); itr != declarations.end(); ++itr) {
		(*itr)->PrintXML(dst, indent+4);
	}
	for(std::vector<Statement*>::const_iterator itr = statements.begin(); itr != statements.end(); ++itr) {
		(*itr)->PrintXML(dst, indent+4);
	}
	dst << spaces(indent+2) << "</Scope>" << std::endl;

	dst << spaces(indent) << "</Function>" << std::endl;
}
