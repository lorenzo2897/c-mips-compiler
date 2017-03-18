#include "SwitchStatement.hpp"
#include "CompoundStatement.hpp"
#include "CaseStatement.hpp"

/* ************************* */

SwitchStatement::SwitchStatement() : Statement(), expression(NULL), statement(NULL) {}
SwitchStatement::SwitchStatement(Expression* e, Statement* s) : Statement(), expression(e), statement(s) {}

void SwitchStatement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent) << "switch(";
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

void SwitchStatement::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	// everything else in this compiler is pretty decent, but this is some ugly code...
	VariableMap sub_bindings = bindings;
	std::string switch_base = unique("switch");
	sub_bindings.break_destination = switch_base + "_end";

	if(!statement) return;
	CompoundStatement* cs = dynamic_cast<CompoundStatement*>(statement);
	if(!cs) {
		// not a compund statement, just evaluate it
		statement->MakeIR(sub_bindings, stack, out);
		return;
	}

	// evaluate the switch expression
	out.push_back(new LabelInstruction(switch_base + "_eval"));
	std::string val = expression->MakeIR(bindings, stack, out);

	// dig into the CompoundStatement: make and initialise all variables
	sub_bindings.add_bindings(cs->scope->declarations);
	stack.add_variables(sub_bindings, cs->scope->declarations);

	// generate instructions for initialisers
	for(std::vector<Declaration*>::const_iterator itr = cs->scope->declarations.begin(); itr != cs->scope->declarations.end(); ++itr) {
		(*itr)->MakeIR_initialisers(sub_bindings, stack, out);
	}

	// collect all of the case statements into a map
	std::map<int32_t, std::string> case_map;
	bool has_default = false;
	for(std::vector<Statement*>::const_iterator itr = cs->scope->statements.begin(); itr != cs->scope->statements.end(); ++itr) {
		CaseStatement* case_st = dynamic_cast<CaseStatement*>(*itr);
		if(case_st) {
			bool is_default;
			int32_t case_value;
			case_st->eval_case(sub_bindings, is_default, case_value);
			// make sure there are no duplicates
			if(is_default) {
				if(has_default) {
					throw compile_error("multiple default labels in one switch", sourceFile, sourceLine);
				} else {
					has_default = true;
				}
			} else {
				if(case_map.count(case_value)) {
					throw compile_error("duplicate case value", sourceFile, sourceLine);
				} else {
					case_map[case_value] = unique(switch_base + "_case");
				}
			}
		}
	}

	// compare the switch expression against each value in the map
	for(std::map<int32_t, std::string>::const_iterator itr = case_map.begin(); itr != case_map.end(); ++itr) {
		out.push_back(new GotoIfEqualInstruction(itr->second, val, itr->first));
	}
	if(has_default) {
		out.push_back(new GotoInstruction(switch_base + "_default"));
	} else {
		out.push_back(new GotoInstruction(switch_base + "_end"));
	}

	// execute the statements, replacing cases with their labels
	out.push_back(new LabelInstruction(switch_base + "_body"));
	for(std::vector<Statement*>::const_iterator itr = cs->scope->statements.begin(); itr != cs->scope->statements.end(); ++itr) {
		CaseStatement* case_st = dynamic_cast<CaseStatement*>(*itr);
		if(case_st) {
			bool is_default;
			int32_t case_value;
			case_st->eval_case(sub_bindings, is_default, case_value);
			if(is_default) {
				out.push_back(new LabelInstruction(switch_base + "_default"));
			} else {
				out.push_back(new LabelInstruction(case_map.at(case_value)));
			}
			case_st->statement->MakeIR(sub_bindings, stack, out);
		} else {
			(*itr)->MakeIR(sub_bindings, stack, out);
		}
	}
	out.push_back(new LabelInstruction(switch_base + "_end"));
}
