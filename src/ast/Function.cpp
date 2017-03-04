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

void Function::CompileIR(VariableMap bindings, std::ostream &dst) const {
	FunctionStack stack;
	IRVector out;

	// populate the bindings with the function parameters and declarations
	bindings.add_bindings(parameters);
	stack.add_variables(bindings, parameters);
	bindings.add_bindings(declarations);
	stack.add_variables(bindings, declarations);

	// generate instructions from statements
	for(std::vector<Statement*>::const_iterator itr = statements.begin(); itr != statements.end(); ++itr) {
		(*itr)->MakeIR(bindings, stack, out);
	}

	// print IR in text form
	dst << function_name << ":" << std::endl;

	dst << "    # stack" << std::endl;
	for(FunctionStack::const_iterator itr = stack.begin(); itr != stack.end(); ++itr) {
		dst << "    " << (*itr).first << " (" << (*itr).second.bytes() << ") " << (*itr).second.name() << std::endl;
	}

	dst << "    # code" << std::endl;
	for(IRVector::const_iterator itr = out.begin(); itr != out.end(); ++itr) {
		(*itr)->Debug(dst);
	}

	dst << "    # end " << function_name << std::endl;
	dst << std::endl;
}
