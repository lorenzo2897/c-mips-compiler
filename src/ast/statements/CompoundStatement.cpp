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
