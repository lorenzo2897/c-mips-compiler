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
