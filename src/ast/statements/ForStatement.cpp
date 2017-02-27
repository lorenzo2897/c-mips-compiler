#include "ForStatement.hpp"

/* ************************* */

ForStatement::ForStatement() :
	Statement(),
	exp_initialiser(NULL),
	exp_condition(NULL),
	exp_iteration(NULL),
	body(NULL) {}

ForStatement::ForStatement(Expression* init, Expression* cond, Expression* iter, Statement* body) :
	Statement(),
	exp_initialiser(init),
	exp_condition(cond),
	exp_iteration(iter),
	body(body) {}

void ForStatement::merge_declarations(Scope *scope) {
	declarations.insert(declarations.end(), scope->declarations.begin(), scope->declarations.end());
}


void ForStatement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "FOR LOOP";

	dst << std::endl << spaces(indent+2) << "Declarations:" << std::endl;
	for(std::vector<Declaration*>::const_iterator itr = declarations.begin(); itr != declarations.end(); ++itr) {
		(*itr)->Debug(dst, indent+4);
	}

	dst << std::endl << spaces(indent+2) << "Initialiser: ";
	if(exp_initialiser)
		exp_initialiser->Debug(dst, indent);

	dst << std::endl << spaces(indent+2) << "Condition: ";
	if(exp_condition)
		exp_condition->Debug(dst, indent);

	dst << std::endl << spaces(indent+2) << "Afterthought: ";
	if(exp_iteration)
		exp_iteration->Debug(dst, indent);

	if(body) {
		body->Debug(dst, indent+2);
	} else {
		dst << " (null statement!)";
	}
}

void ForStatement::PrintXML(std::ostream& dst, int indent) const {
	dst << spaces(indent) << "<Scope>" << std::endl;
	for(std::vector<Declaration*>::const_iterator itr = declarations.begin(); itr != declarations.end(); ++itr) {
		(*itr)->PrintXML(dst, indent+2);
	}
	if (body) {
		body->PrintXML(dst, indent+2);
	}
	dst << spaces(indent) << "</Scope>" << std::endl;
}
