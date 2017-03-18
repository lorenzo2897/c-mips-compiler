#include "CaseStatement.hpp"


/* ************************* */

CaseStatement::CaseStatement() : Statement(), case_match(NULL), statement(NULL) {}
CaseStatement::CaseStatement(Expression* e, Statement* s) : Statement(), case_match(e), statement(s) {}

void CaseStatement::Debug(std::ostream& dst, int indent) const {
	dst << std::endl << spaces(indent>=2 ? indent-2 : indent) << "Case ";
	if(case_match)
		case_match->Debug(dst, indent);
	else
		dst << "default";
	dst << ": ";
	if(statement) {
		statement->Debug(dst, indent);
	} else {
		dst << " (null statement!)";
	}
}

void CaseStatement::MakeIR(VariableMap const& bindings, FunctionStack& stack, IRVector& out) const {
	throw compile_error("'case' statement not in switch statement", sourceFile, sourceLine);
}

void CaseStatement::eval_case(VariableMap const& bindings, bool& is_default, int32_t& value) const {
	if(case_match) {
		is_default = false;
		try {
			value = case_match->evaluate_int(bindings);
		} catch (compile_error e) {
			throw compile_error((std::string) "expression in 'case' statement is not an integer constant expression\n" + e.what(), sourceFile, sourceLine);
		}
	} else {
		is_default = true;
		value = 0;
	}
}
