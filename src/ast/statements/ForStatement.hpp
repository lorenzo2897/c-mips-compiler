#ifndef AST_FOR_STATEMENT_H
#define AST_FOR_STATEMENT_H

#include <string>
#include <vector>

#include "../Node.hpp"
#include "../Scope.hpp"
#include "../Statement.hpp"
#include "../Expression.hpp"
#include "../Declaration.hpp"

/* ************************* */

class ForStatement : public Statement {
public:
	ForStatement();
	ForStatement(Expression* init, Expression* cond, Expression* iter, Statement* body);

    std::vector<Declaration*> declarations;
	Expression* exp_initialiser;
	Expression* exp_condition;
	Expression* exp_iteration;
	Statement* body;

	void merge_declarations(Scope* scope);

	virtual void Debug(std::ostream& dst, int indent) const;
};

#endif
