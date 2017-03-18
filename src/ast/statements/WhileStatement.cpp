#include "WhileStatement.hpp"

/* ************************* */

WhileStatement::WhileStatement() : Statement(), expression(NULL), statement(NULL), statement_before_condition(false) {}
WhileStatement::WhileStatement(Expression* e, Statement* s, bool statement_before_condition) : Statement(), expression(e), statement(s), statement_before_condition(statement_before_condition) {}

void WhileStatement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << (statement_before_condition ? "do_while (" : "while (");
	if(expression)
		expression->Debug(dst, indent);
	else
		dst << "null expression";
	dst << ")";
	if(statement) {
		statement->Debug(dst, indent);
	} else {
		dst << " (null statement!)";
	}
}

void WhileStatement::PrintXML(std::ostream& dst, int indent) const {
	if(statement) statement->PrintXML(dst, indent);
}

void WhileStatement::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	/*
	while_begin:
	  condition
	  beqz while_end
	  body
	  goto while_begin
	while_end:
	*/

	/*
	while_begin:
	  body
	  condition
	  beqz while_end
	  goto while_begin
	while_end:
	*/
	std::string while_label = unique("while");
	out.push_back(new LabelInstruction(while_label + "_begin"));

	if(statement_before_condition) { // do {} while()
		if(statement) statement->MakeIR(bindings, stack, out);
	}

	std::string cond_res = expression->MakeIR(bindings, stack, out); //condition
	out.push_back(new GotoIfZeroInstruction(while_label + "_end", cond_res)); //beqz

	if(!statement_before_condition) { // while() {}
		if(statement) statement->MakeIR(bindings, stack, out);
	}

	out.push_back(new GotoInstruction(while_label + "_begin"));
	out.push_back(new LabelInstruction(while_label + "_end"));
}
