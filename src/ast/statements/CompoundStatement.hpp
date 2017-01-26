#ifndef AST_COMPOUND_STATEMENT_H
#define AST_COMPOUND_STATEMENT_H

#include <string>
#include <vector>

#include "../Node.hpp"
#include "../Statement.hpp"
#include "../Scope.hpp"

class Scope; // circular dependency between Scope and CompoundStatement

/* ************************* */

class CompoundStatement : public Statement {
public:
	CompoundStatement();
	CompoundStatement(Scope* s);

	Scope* scope;
	virtual void Debug(std::ostream& dst, int indent) const;
};

#endif
