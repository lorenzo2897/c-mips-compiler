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

void ForStatement::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	/*
	for_begin:
	  initialiser
	for_condition:
	  condition
	  beqz for_end
	for_body:
	  body
	for_afterthought:
	  afterthought
	  goto for_condition
	for_end:
	*/

	// obtain a unique label group
	std::string for_label = unique("for");

	// add myself to the break/continue bindings
	VariableMap for_bindings = bindings;
	for_bindings.break_destination = for_label + "_end";
	for_bindings.continue_destination = for_label + "_condition";

	// emit instructions

	// begin
	out.push_back(new LabelInstruction(for_label + "_begin"));
	if(exp_initialiser) exp_initialiser->MakeIR(for_bindings, stack, out);

	// condition
	out.push_back(new LabelInstruction(for_label + "_condition"));
	if(exp_condition) {
		std::string cond_res = exp_condition->MakeIR(for_bindings, stack, out);
		out.push_back(new GotoIfEqualInstruction(for_label + "_end", cond_res, 0));
	} else {
		// empty condition evaluates to true, so just fall through to body
	}

	// body
	out.push_back(new LabelInstruction(for_label + "_body"));
	if(body) body->MakeIR(for_bindings, stack, out);

	// afterthought
	out.push_back(new LabelInstruction(for_label + "_afterthought"));
	if(exp_iteration) exp_iteration->MakeIR(for_bindings, stack, out);
	out.push_back(new GotoInstruction(for_label + "_condition"));

	// end
	out.push_back(new LabelInstruction(for_label + "_end"));
}
