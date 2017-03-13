#include "CompoundStatement.hpp"


/* ************************* */

CompoundStatement::CompoundStatement() : Statement(), scope(NULL) {}

CompoundStatement::CompoundStatement(Scope* s) : Statement(), scope(s) {}

void CompoundStatement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "{";

	if(scope) {
		dst << std::endl << spaces(indent+2) << "Declarations:" << std::endl;
		for(std::vector<Declaration*>::const_iterator itr = scope->declarations.begin(); itr != scope->declarations.end(); ++itr) {
			(*itr)->Debug(dst, indent+4);
		}

		if(scope->statements.size() > 0) {
			dst << spaces(indent+2) << "Body: ";
			for(std::vector<Statement*>::const_iterator itr = scope->statements.begin(); itr != scope->statements.end(); ++itr) {
				(*itr)->Debug(dst, indent+4);
			}
		} else {
			dst << spaces(indent+2) << "Body: empty";
		}
	} else {
		dst << "null expression";
	}

	dst << std::endl << spaces(indent) << "}";
}

void CompoundStatement::PrintXML(std::ostream& dst, int indent) const {
	dst << spaces(indent) << "<Scope>" << std::endl;
	if (scope) {
		for(std::vector<Declaration*>::const_iterator itr = scope->declarations.begin(); itr != scope->declarations.end(); ++itr) {
			(*itr)->PrintXML(dst, indent+2);
		}
		for(std::vector<Statement*>::const_iterator itr = scope->statements.begin(); itr != scope->statements.end(); ++itr) {
			(*itr)->PrintXML(dst, indent+2);
		}
	}
	dst << spaces(indent) << "</Scope>" << std::endl;
}

void CompoundStatement::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	// add bindings and stack entries for my declarations
	VariableMap sub_bindings = bindings;
	sub_bindings.add_bindings(scope->declarations);
	stack.add_variables(sub_bindings, scope->declarations);

	// generate instructions for initialisers
	for(std::vector<Declaration*>::const_iterator itr = scope->declarations.begin(); itr != scope->declarations.end(); ++itr) {
		if((*itr)->initialiser) {
			std::string src = (*itr)->initialiser->MakeIR(sub_bindings, stack, out);
			std::string dst = unique((std::string)"addr_" + (*itr)->identifier + "_");
			stack[dst] = sub_bindings.at((*itr)->identifier).type.addressof();
			out.push_back(new AddressOfInstruction(dst, sub_bindings.at((*itr)->identifier).alias));
			out.push_back(new AssignInstruction(dst, src));
		}

	}

	// recurse into my own list of statements
	for(std::vector<Statement*>::const_iterator itr = scope->statements.begin(); itr != scope->statements.end(); ++itr) {
		(*itr)->MakeIR(sub_bindings, stack, out);
	}
}
