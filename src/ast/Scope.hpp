#ifndef AST_SCOPE_H
#define AST_SCOPE_H

#include <vector>

#include "Node.hpp"
#include "Declaration.hpp"
#include "Statement.hpp"


class Statement; // circular dependency between Scope and CompoundStatement


class Scope : public Node {

protected:

public:
	Scope();

    std::vector<Declaration*> declarations;
	std::vector<Statement*> statements;

	void declare(Declaration* d);
	void add_statement(Statement* s);

	void merge_declarations(Scope* scope);
	void merge_statements(Scope* scope);
};

#endif
